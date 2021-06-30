/* Copyright 2021 Enjin Pte Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "PusherClient.hpp"

#include "RapidJsonUtils.hpp"
#include "PusherConstants.hpp"
#include "PusherErrorCodes.hpp"
#include "PusherException.hpp"
#include <sstream>

namespace enjin::pusher {

static constexpr char CHANNEL_KEY[] = "channel";
static constexpr char DATA_KEY[] = "data";
static constexpr char EVENT_KEY[] = "event";

std::string get_subscription_message_for_channel_name(const std::string& channel_name) {
    rapidjson::Document document(rapidjson::kObjectType);
    auto& allocator = document.GetAllocator();

    sdk::utils::set_string_member(document, EVENT_KEY, PusherConstants::CHANNEL_SUBSCRIBE);

    rapidjson::Value v_data(rapidjson::kObjectType);
    rapidjson::Value v_channel;
    v_channel.SetString(channel_name.c_str(), allocator);

    v_data.AddMember(CHANNEL_KEY, v_channel, allocator);
    document.AddMember(DATA_KEY, v_data, allocator);

    return sdk::utils::document_to_string(document);
}

PusherClient::PusherClient(std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client,
                           std::string key,
                           const PusherOptions& options,
                           std::shared_ptr<sdk::utils::LoggerProvider> logger_provider)
        : ws_client(std::move(ws_client)),
          logger_provider(std::move(logger_provider)),
          key(std::move(key)),
          options(options) {
    PusherClient::ws_client->set_allow_reconnecting(true);
    PusherClient::ws_client->set_allowed_reconnect_attempts(5);

    PusherClient::ws_client->set_message_handler([this](const std::string& message) {
        websocket_message_received(message);
    });
    PusherClient::ws_client->set_open_handler([this]() {
        websocket_opened();
    });
    PusherClient::ws_client->set_close_handler([this](int close_status, const std::string& message) {
        websocket_closed(close_status, message);
    });
}

PusherClient::~PusherClient() {
    ws_client->close().get();
}

std::future<void> PusherClient::connect() {
    ws_client_closed = false;
    ws_client->set_allow_reconnecting(true);
    set_state(PusherConnectionState::CONNECTING);

    std::string schema = options.is_encrypted()
                         ? PusherConstants::SECURE_SCHEMA
                         : PusherConstants::INSECURE_SCHEMA;

    std::stringstream uri_ss;
    uri_ss << schema
           << options.host()
           << "/app/"
           << key
           << "?protocol=5&client=enjin-cpp-pusher-client";

#ifdef ENJINSDK_VERSION
    uri_ss << "&version=" << ENJINSDK_VERSION;
#endif

    return ws_client->connect(uri_ss.str());
}

std::future<void> PusherClient::disconnect() {
    PusherConnectionState present_state = get_state();
    if (present_state == PusherConnectionState::CONNECTED || present_state == PusherConnectionState::CONNECTING) {
        set_state(PusherConnectionState::DISCONNECTING);
        ws_client_closed = true;

        return std::async([this]() {
            ws_client->close().get();
            set_state(PusherConnectionState::DISCONNECTED);
        });
    }

    return std::async([]() {});
}

std::future<void> PusherClient::subscribe(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        std::unique_lock<std::mutex> channels_lock(channels_mutex);
        std::unique_lock<std::mutex> pending_lock(pending_channels_mutex);

        bool is_pending = pending_channels.find(channel_name) != pending_channels.end();
        auto loc = channels.find(channel_name);
        bool is_subscribed = loc != channels.end() && loc->second.is_subscribed;

        if (is_pending || is_subscribed) {
            return;
        }

        pending_channels.emplace(channel_name);
        pending_lock.unlock();

        channels.try_emplace(channel_name, PusherChannel{});
        channels_lock.unlock();

        if (get_state() == PusherConnectionState::CONNECTED) {
            subscribe_to_channel(channel_name).get();
        }
    });
}

std::future<void> PusherClient::subscribe_to_channel(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        ws_client->send(get_subscription_message_for_channel_name(channel_name));

        std::unique_lock<std::mutex> channels_lock(channels_mutex);
        auto loc = channels.find(channel_name);
        bool subscribed = loc != channels.end() && loc->second.is_subscribed;
        channels_lock.unlock();

        auto time_point = std::chrono::steady_clock::now() + options.get_client_timeout();

        std::unique_lock<std::mutex> subscription_lock(subscription_mutex);

        while (!subscribed) {
            auto status = subscription_cv.wait_until(subscription_lock, time_point);
            if (status == std::cv_status::timeout) {
                // TODO: Have the client erase the channel if timeout is reached.

                throw PusherException("", 0); // TODO: Switch to a timeout exception.
            }

            channels_lock.lock();
            loc = channels.find(channel_name);
            subscribed = loc != channels.end() && loc->second.is_subscribed;
            channels_lock.unlock();
        }
    });
}

std::future<void> PusherClient::unsubscribe(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        if (get_state() != PusherConnectionState::CONNECTED) {
            return;
        }

        // TODO: Check (if necessary) whether the client is subscribed or pending subscription to the channel.

        rapidjson::Document document(rapidjson::kObjectType);
        auto& allocator = document.GetAllocator();

        sdk::utils::set_string_member(document, EVENT_KEY, PusherConstants::CHANNEL_UNSUBSCRIBE);

        rapidjson::Value v_data(rapidjson::kObjectType);
        rapidjson::Value v_channel;
        v_channel.SetString(channel_name.c_str(), allocator);

        v_data.AddMember(CHANNEL_KEY, v_channel, allocator);
        document.AddMember(DATA_KEY, v_data, allocator);

        ws_client->send(sdk::utils::document_to_string(document));

        channels_mutex.lock();
        channels.erase(channel_name);
        channels_mutex.unlock();
    });
}

void PusherClient::subscription_succeeded(const std::string& channel_name) {
    std::unique_lock<std::mutex> pending_lock(pending_channels_mutex);
    auto pending_loc = pending_channels.find(channel_name);
    if (pending_loc != pending_channels.end()) {
        pending_channels.erase(pending_loc);
    }
    pending_lock.unlock();

    std::unique_lock<std::mutex> channels_lock(channels_mutex);
    auto channels_loc = channels.find(channel_name);
    if (channels_loc != channels.end()) {
        channels_loc->second.is_subscribed = true;
    }
    channels_lock.unlock();

    std::unique_lock<std::mutex> subscription_lock(subscription_mutex);
    subscription_cv.notify_all();
}

void PusherClient::bind(const std::string& event_name, std::shared_ptr<ISubscriptionEventListener> listener) {
    std::vector<std::shared_ptr<ISubscriptionEventListener>> vector({std::move(listener)});

    std::lock_guard<std::mutex> guard(event_listeners_mutex);

    // Adds the listener to the already existing vector if try-emplace fails
    if (!event_listeners.try_emplace(event_name, vector).second) {
        event_listeners[event_name].push_back(listener);
    }
}

void PusherClient::unbind(const std::string& event_name) {
    event_listeners_mutex.lock();

    auto iter = event_listeners.find(event_name);
    if (iter != event_listeners.end()) {
        event_listeners.erase(iter);
    }

    event_listeners_mutex.unlock();
}

bool PusherClient::is_subscribed_or_pending(const std::string& channel_name) const {
    return is_subscription_pending(channel_name) || is_subscribed(channel_name);
}

bool PusherClient::is_subscribed(const std::string& channel_name) const {
    std::lock_guard<std::mutex> guard(channels_mutex);
    auto loc = channels.find(channel_name);
    return loc != channels.end() && loc->second.is_subscribed;
}

bool PusherClient::is_subscription_pending(const std::string& channel_name) const {
    std::lock_guard<std::mutex> guard(pending_channels_mutex);
    return pending_channels.find(channel_name) != pending_channels.end();
}

PusherConnectionState PusherClient::get_state() const {
    std::lock_guard<std::mutex> guard(state_mutex);
    return state;
}

void PusherClient::set_state(PusherConnectionState state) {
    state_mutex.lock();
    PusherClient::state = state;
    state_mutex.unlock();

    if (on_connection_state_change.has_value()) {
        on_connection_state_change.value()(state);
    }
}

void PusherClient::set_on_connection_state_change_handler(const std::function<void(PusherConnectionState)>& handler) {
    on_connection_state_change = handler;
}

void PusherClient::set_on_error_handler(const std::function<void(const std::exception&)>& handler) {
    on_error = handler;
}

void PusherClient::emit_event(const PusherEvent& event) {
    if (!event.get_event_name().has_value()) {
        return;
    }

    const std::string& event_name = event.get_event_name().value();

    std::lock_guard<std::mutex> guard(event_listeners_mutex);

    auto loc = event_listeners.find(event_name);
    if (loc != event_listeners.end()) {
        for (const auto& listener : loc->second) {
            listener->on_event(event);
        }
    }
}

void PusherClient::websocket_message_received(const std::string& message) {
    // Processes the incoming message
    rapidjson::Document document;
    document.Parse(message.c_str());

    if (!document.IsObject()) {
        return;
    } else if (document.HasMember(DATA_KEY) && document[DATA_KEY].IsObject()) {
        sdk::utils::set_string_member(document, DATA_KEY, sdk::utils::get_object_as_string(document, DATA_KEY));
    }

    struct Message {
        std::string event;
        std::string channel;
        std::string data;
    };

    PusherEvent event;
    event.deserialize(sdk::utils::document_to_string(document));

    // Struct for easier access of event data
    struct Message msg{
            event.get_event_name().value_or(""),
            event.get_channel_name().value_or(""),
            event.get_data().value_or("")
    };

    emit_event(event);

    if (msg.event.find(PusherConstants::PUSHER_MESSAGE_PREFIX) == 0) {
        if (msg.event == PusherConstants::CHANNEL_SUBSCRIPTION_SUCCEEDED) {
            subscription_succeeded(msg.channel);
        } else if (msg.event == PusherConstants::CHANNEL_SUBSCRIPTION_ERROR && on_error.has_value()) {
            on_error.value()(PusherException("Error received on channel subscription: " + message,
                                             (int) PusherErrorCodes::SUBSCRIPTION_ERROR));
        }
    }
}

void PusherClient::websocket_opened() {
    set_state(PusherConnectionState::CONNECTED);

    std::lock_guard<std::mutex> guard(channels_mutex);
    for (const auto& entry : channels) {
        ws_client->send(get_subscription_message_for_channel_name(entry.first));
    }
}

void PusherClient::websocket_closed(int close_status, const std::string&) {
    if (get_state() == PusherConnectionState::DISCONNECTED) {
        logger_provider->log(sdk::utils::LogLevel::WARN, "Pusher client received close message while disconnected");
        return;
    }

    /* 4000-4099 codes from Pusher indicate reconnection should not be attempted.
     * https://pusher.com/docs/pusher_protocol#error-codes
     */
    if (close_status >= 4000 && close_status < 4100) {
        ws_client->set_allow_reconnecting(false);
        set_state(PusherConnectionState::DISCONNECTED);
        return;
    }

    if (!ws_client_closed) {
        set_state(PusherConnectionState::RECONNECTING);
    }
}

}
