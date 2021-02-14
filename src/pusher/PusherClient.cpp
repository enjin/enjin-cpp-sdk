#include "enjinsdk/internal/pusher/PusherClient.hpp"

#include "RapidJsonUtils.hpp"
#include "enjinsdk/internal/pusher/Constants.hpp"
#include "enjinsdk/internal/pusher/ErrorCodes.hpp"
#include "enjinsdk/internal/pusher/PusherException.hpp"
#include <algorithm>
#include <sstream>
#include <utility>

namespace enjin::pusher {

static constexpr char CHANNEL_KEY[] = "channel";
static constexpr char DATA_KEY[] = "data";
static constexpr char EVENT_KEY[] = "event";

PusherClient::PusherClient(std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client,
                           const std::string& key,
                           PusherOptions& options)
        : ws_client(std::move(ws_client)), key(key), options(options) {
    PusherClient::ws_client->set_message_handler([this](const std::string& message) {
        websocket_message_received(message);
    });
    PusherClient::ws_client->set_close_handler([this](int close_status,
                                                      const std::string& message,
                                                      const std::error_code& error) {
        websocket_closed(close_status, message, error);
    });
}

std::future<void> PusherClient::connect(const std::function<void(ConnectionState state)>& on_connection_state_change,
                                        const std::function<void(const std::exception&)>& on_error) {
    PusherClient::on_connection_state_change = on_connection_state_change;
    PusherClient::on_error = on_error;

    return std::async([this]() {
        set_state(ConnectionState::CONNECTING);

        std::string schema = options.is_encrypted()
                             ? Constants::SECURE_SCHEMA
                             : Constants::INSECURE_SCHEMA;

        /* TODO: The client query fragment "client=enjin-cpp-pusher-client" may not work with the server since it is not
         *       a official Pusher client.
         */
        ws_client->connect((std::stringstream()
                << schema
                << options.host()
                << "/app/"
                << key
                << "?protocol=5&client=enjin-cpp-pusher-client&version=1.0.0"
                           ).str()).wait();
        set_state(ConnectionState::CONNECTED);
    });
}

std::future<void> PusherClient::disconnect() {
    if (get_state() == ConnectionState::CONNECTED) {
        set_state(ConnectionState::DISCONNECTING);

        return std::async([this]() {
            ws_client->close().wait();
            set_state(ConnectionState::DISCONNECTED);
        });
    } else {
        return std::async([this]() {
            set_state(ConnectionState::DISCONNECTED);
        });
    }
}

std::future<void> PusherClient::subscribe(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        channels_lock.lock();

        if (already_subscribed(channel_name)) {
            channels_lock.unlock();
            return;
        }

        pending_channels.emplace(channel_name);

        channels_lock.unlock();

        subscribe_to_channel(channel_name).wait();
    });
}

std::future<void> PusherClient::subscribe_to_channel(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        channels_lock.lock();

        channels.try_emplace(channel_name, PusherChannel{});

        if (get_state() == ConnectionState::CONNECTED) {
            rapidjson::Document document(rapidjson::kObjectType);
            auto& allocator = document.GetAllocator();

            sdk::utils::set_string_member(document, EVENT_KEY, Constants::CHANNEL_SUBSCRIBE);

            rapidjson::Value v_data(rapidjson::kObjectType);
            rapidjson::Value v_channel;
            v_channel.SetString(channel_name.c_str(), allocator);

            v_data.AddMember(CHANNEL_KEY, v_channel, allocator);
            document.AddMember(DATA_KEY, v_data, allocator);

            ws_client->send(sdk::utils::document_to_string(document)).wait();
        }

        channels_lock.unlock();
    });
}

std::future<void> PusherClient::unsubscribe(const std::string& channel_name) {
    if (get_state() == ConnectionState::CONNECTED) {
        return std::async([this, channel_name]() {
            rapidjson::Document document(rapidjson::kObjectType);
            auto& allocator = document.GetAllocator();

            sdk::utils::set_string_member(document, EVENT_KEY, Constants::CHANNEL_UNSUBSCRIBE);

            rapidjson::Value v_data(rapidjson::kObjectType);
            rapidjson::Value v_channel;
            v_channel.SetString(channel_name.c_str(), allocator);

            v_data.AddMember(CHANNEL_KEY, v_channel, allocator);
            document.AddMember(DATA_KEY, v_data, allocator);

            ws_client->send(sdk::utils::document_to_string(document)).wait();

            channels_lock.lock();
            channels.erase(channel_name);
            channels_lock.unlock();
        });
    }

    return std::future<void>(); // Do nothing since this was not connected;
}

bool PusherClient::already_subscribed(const std::string& channel_name) {
    if (pending_channels.find(channel_name) != pending_channels.end()) {
        return true;
    }

    auto loc = channels.find(channel_name);
    return loc != channels.end() && loc->second.is_subscribed;
}

void PusherClient::subscription_succeeded(const std::string& channel_name) {
    auto pending_loc = pending_channels.find(channel_name);
    if (pending_loc != pending_channels.end()) {
        pending_channels.erase(pending_loc);
    }

    auto channels_loc = channels.find(channel_name);
    if (channels_loc != channels.end()) {
        channels_loc->second.is_subscribed = true;
    }
}

void PusherClient::bind(const std::string& event_name, std::shared_ptr<ISubscriptionEventListener> listener) {
    std::vector<std::shared_ptr<ISubscriptionEventListener>> vector({std::move(listener)});

    event_listeners_lock.lock();

    // Adds the listener to the already existing vector if try-emplace fails
    if (!event_listeners.try_emplace(event_name, vector).second) {
        event_listeners[event_name].push_back(listener);
    }

    event_listeners_lock.unlock();
}

void PusherClient::unbind(const std::string& event_name) {
    event_listeners_lock.lock();

    auto iter = event_listeners.find(event_name);
    if (iter != event_listeners.end()) {
        event_listeners.erase(iter);
    }

    event_listeners_lock.unlock();
}

ConnectionState PusherClient::get_state() {
    state_lock.lock();
    ConnectionState state = PusherClient::state;
    state_lock.unlock();
    return state;
}

void PusherClient::set_state(ConnectionState state) {
    state_lock.lock();
    PusherClient::state = state;
    state_lock.unlock();
    on_connection_state_change(state);
}

void PusherClient::emit_event(const PusherEvent& event) {
    if (!event.get_event_name().has_value()) {
        return;
    }

    const std::string& event_name = event.get_event_name().value();

    event_listeners_lock.lock();

    auto loc = event_listeners.find(event_name);
    if (loc != event_listeners.end()) {
        for (const auto& listener : loc->second) {
            listener->on_event(event);
        }
    }

    event_listeners_lock.unlock();
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

    if (msg.event.find(Constants::PUSHER_MESSAGE_PREFIX) == 0) {
        if (msg.event == Constants::CHANNEL_SUBSCRIPTION_SUCCEEDED) {
            subscription_succeeded(msg.channel);
        } else if (msg.event == Constants::CHANNEL_SUBSCRIPTION_ERROR) {
            on_error(PusherException("Error received on channel subscription: " + message,
                                     (int) ErrorCodes::SUBSCRIPTION_ERROR));
        }
    }
}

void PusherClient::websocket_closed(int close_status, const std::string& message, const std::error_code& error) {
    set_state(ConnectionState::DISCONNECTED);
    // TODO: Try reconnecting.
}

}
