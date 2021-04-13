#include "PusherClient.hpp"

#include "RapidJsonUtils.hpp"
#include "Constants.hpp"
#include "ErrorCodes.hpp"
#include "PusherException.hpp"
#include <exception>
#include <sstream>

namespace enjin::pusher {

static constexpr char CHANNEL_KEY[] = "channel";
static constexpr char DATA_KEY[] = "data";
static constexpr char EVENT_KEY[] = "event";

std::string get_subscription_message_for_channel_name(const std::string& channel_name) {
    rapidjson::Document document(rapidjson::kObjectType);
    auto& allocator = document.GetAllocator();

    sdk::utils::set_string_member(document, EVENT_KEY, Constants::CHANNEL_SUBSCRIBE);

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
                           std::shared_ptr<sdk::utils::Logger> logger)
        : ws_client(std::move(ws_client)),
          logger(std::move(logger)),
          key(std::move(key)),
          options(options) {
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
    ws_client->close();
}

void PusherClient::connect() {
    ws_client_closed = false;
    ws_client->set_allow_reconnecting(true);
    set_state(ConnectionState::CONNECTING);

    std::string schema = options.is_encrypted()
                         ? Constants::SECURE_SCHEMA
                         : Constants::INSECURE_SCHEMA;

    std::stringstream uri_ss;
    uri_ss << schema
           << options.host()
           << "/app/"
           << key
           << "?protocol=5&client=enjin-cpp-pusher-client";

#ifdef ENJINSDK_VERSION
    uri_ss << "&version=" << ENJINSDK_VERSION;
#endif

    ws_client->connect(uri_ss.str());
}

void PusherClient::disconnect() {
    ConnectionState present_state = get_state();
    if (present_state == ConnectionState::CONNECTED || present_state == ConnectionState::CONNECTING) {
        set_state(ConnectionState::DISCONNECTING);
        ws_client_closed = true;
        ws_client->close();
    }

    set_state(ConnectionState::DISCONNECTED);
}

std::future<void> PusherClient::subscribe(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        channels_lock.lock();
        pending_channels_lock.lock();

        bool is_pending = pending_channels.find(channel_name) != pending_channels.end();
        auto loc = channels.find(channel_name);
        bool is_subscribed = loc != channels.end() && loc->second.is_subscribed;

        if (is_pending || is_subscribed) {
            channels_lock.unlock();
            pending_channels_lock.unlock();
            return;
        }

        pending_channels.emplace(channel_name);

        channels_lock.unlock();
        pending_channels_lock.unlock();

        subscribe_to_channel(channel_name).get();
    });
}

std::future<void> PusherClient::subscribe_to_channel(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        std::lock_guard<std::mutex> guard(channels_lock);

        channels.try_emplace(channel_name, PusherChannel{});

        // Determines if message can be sent immediately
        if (get_state() == ConnectionState::CONNECTED) {
            ws_client->send(get_subscription_message_for_channel_name(channel_name));
        }
    });
}

std::future<void> PusherClient::unsubscribe(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        rapidjson::Document document(rapidjson::kObjectType);
        auto& allocator = document.GetAllocator();

        sdk::utils::set_string_member(document, EVENT_KEY, Constants::CHANNEL_UNSUBSCRIBE);

        rapidjson::Value v_data(rapidjson::kObjectType);
        rapidjson::Value v_channel;
        v_channel.SetString(channel_name.c_str(), allocator);

        v_data.AddMember(CHANNEL_KEY, v_channel, allocator);
        document.AddMember(DATA_KEY, v_data, allocator);

        if (get_state() == ConnectionState::CONNECTED) {
            ws_client->send(sdk::utils::document_to_string(document));
        }

        channels_lock.lock();
        channels.erase(channel_name);
        channels_lock.unlock();
    });
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

    std::lock_guard<std::mutex> guard(event_listeners_lock);

    // Adds the listener to the already existing vector if try-emplace fails
    if (!event_listeners.try_emplace(event_name, vector).second) {
        event_listeners[event_name].push_back(listener);
    }
}

void PusherClient::unbind(const std::string& event_name) {
    event_listeners_lock.lock();

    auto iter = event_listeners.find(event_name);
    if (iter != event_listeners.end()) {
        event_listeners.erase(iter);
    }

    event_listeners_lock.unlock();
}

bool PusherClient::is_subscribed_or_pending(const std::string& channel_name) {
    return is_subscription_pending(channel_name) || is_subscribed(channel_name);
}

bool PusherClient::is_subscribed(const std::string& channel_name) {
    std::lock_guard<std::mutex> guard(channels_lock);
    auto loc = channels.find(channel_name);
    return loc != channels.end() && loc->second.is_subscribed;
}

bool PusherClient::is_subscription_pending(const std::string& channel_name) {
    std::lock_guard<std::mutex> guard(pending_channels_lock);
    return pending_channels.find(channel_name) != pending_channels.end();
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

    if (on_connection_state_change.has_value()) {
        on_connection_state_change.value()(state);
    }
}

void PusherClient::set_on_connection_state_change_handler(const std::function<void(ConnectionState)>& handler) {
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

    std::lock_guard<std::mutex> guard(event_listeners_lock);

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

    if (msg.event.find(Constants::PUSHER_MESSAGE_PREFIX) == 0) {
        if (msg.event == Constants::CHANNEL_SUBSCRIPTION_SUCCEEDED) {
            subscription_succeeded(msg.channel);
        } else if (msg.event == Constants::CHANNEL_SUBSCRIPTION_ERROR && on_error.has_value()) {
            on_error.value()(PusherException("Error received on channel subscription: " + message,
                                             (int) ErrorCodes::SUBSCRIPTION_ERROR));
        }
    }
}

void PusherClient::websocket_opened() {
    set_state(ConnectionState::CONNECTED);

    std::lock_guard<std::mutex> guard(channels_lock);
    for (const auto& entry : channels) {
        ws_client->send(get_subscription_message_for_channel_name(entry.first));
    }
}

void PusherClient::websocket_closed(int close_status, const std::string&) {
    if (get_state() == ConnectionState::DISCONNECTED) {
        logger->log(sdk::utils::LogLevel::WARN, "Pusher client received close message while disconnected");
        return;
    }

    /* 4000-4099 codes from Pusher indicate reconnection should not be attempted.
     * https://pusher.com/docs/pusher_protocol#error-codes
     */
    if (close_status >= 4000 && close_status < 4100) {
        ws_client->set_allow_reconnecting(false);
        set_state(ConnectionState::DISCONNECTED);
        return;
    }

    if (!ws_client_closed) {
        set_state(ConnectionState::RECONNECTING);
    }
}

}
