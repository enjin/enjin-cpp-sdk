#include "enjinsdk/internal/pusher/PusherClient.hpp"

#include "RapidJsonUtils.hpp"
#include "enjinsdk/internal/pusher/Constants.hpp"
#include <algorithm>
#include <sstream>
#include <utility>

namespace enjin::pusher {

PusherClient::PusherClient(std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client,
                           const std::string& key,
                           PusherOptions& options)
        : ws_client(std::move(ws_client)), key(key), options(options) {
    // Handle unexpected closures
    ws_client->set_close_handler([this](int close_status,
                                        const std::string& message,
                                        const std::error_code& error) {
        set_state(ConnectionState::DISCONNECTED);
        // TODO: Try reconnecting.
    });
}

std::future<void> PusherClient::connect(const std::function<void(ConnectionState state)>& on_connection_state_change,
                                        const std::function<void(const std::string&,
                                                                 const std::string&,
                                                                 const std::exception&)>& on_error) {
    PusherClient::on_connection_state_change = on_connection_state_change;
    PusherClient::on_error = on_error;

    return std::async([this]() {
        set_state(ConnectionState::CONNECTING);

        std::string schema = options.is_encrypted()
                             ? Constants::SECURE_SCHEMA
                             : Constants::INSECURE_SCHEMA;

        /* TODO: The client query fragment "client=enjin-cpp-pusher-client" may not work with the server since it is not a
         *       official Pusher client.
         */
        ws_client->connect((std::stringstream()
                << schema
                << options.host()
                << "/app/"
                << key
                << "?protocol=5&client=enjin-cpp-pusher-client&version=1.0.0"
                           ).str());
    });
}

std::future<void> PusherClient::disconnect() {
    if (get_state() == ConnectionState::CONNECTED) {
        set_state(ConnectionState::DISCONNECTING);

        return std::async([this]() {
            ws_client->close().wait();
            set_state(ConnectionState::DISCONNECTED);
        });
    }

    return std::future<void>(); // Do nothing since this was not connected;
}

std::future<PusherClient::PusherChannel> PusherClient::subscribe(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        channels_lock.lock();

        if (already_subscribed(channel_name)) {
            PusherChannel pusher_channel = channels[channel_name];
            channels_lock.unlock();
            return pusher_channel;
        }

        pending_channels.emplace_back(channel_name);

        channels_lock.unlock();

        return subscribe_to_channel(channel_name).get();
    });
}

std::future<PusherClient::PusherChannel> PusherClient::subscribe_to_channel(const std::string& channel_name) {
    return std::async([this, channel_name]() {
        channels_lock.lock();

        if (channels.find(channel_name) == channels.end()) {
            channels.emplace(channel_name, PusherChannel(channel_name, shared_from_this()));
        }

        if (get_state() == ConnectionState::CONNECTED) {
            rapidjson::Document document(rapidjson::kObjectType);
            auto& allocator = document.GetAllocator();

            sdk::utils::set_string_member(document, "event", Constants::CHANNEL_SUBSCRIBE);

            rapidjson::Value v_data(rapidjson::kObjectType);
            rapidjson::Value v_channel;
            v_channel.SetString(channel_name.c_str(), allocator);

            v_data.AddMember("channel", v_channel, allocator);
            document.AddMember("data", v_data, allocator);

            ws_client->send(sdk::utils::document_to_string(document)).wait();
        }

        PusherChannel pusherChannel = channels[channel_name];

        channels_lock.unlock();

        return pusherChannel;
    });
}

std::future<void> PusherClient::unsubscribe(const std::string& channel_name) {
    if (get_state() == ConnectionState::CONNECTED) {
        return std::async([this, channel_name]() {
            rapidjson::Document document(rapidjson::kObjectType);
            auto& allocator = document.GetAllocator();

            sdk::utils::set_string_member(document, "event", Constants::CHANNEL_UNSUBSCRIBE);

            rapidjson::Value v_data(rapidjson::kObjectType);
            rapidjson::Value v_channel;
            v_channel.SetString(channel_name.c_str(), allocator);

            v_data.AddMember("channel", v_channel, allocator);
            document.AddMember("data", v_data, allocator);

            ws_client->send(sdk::utils::document_to_string(document)).wait();

            channels_lock.lock();
            channels.erase(channel_name);
            channels_lock.unlock();
        });
    }

    return std::future<void>(); // Do nothing since this was not connected;
}

bool PusherClient::already_subscribed(const std::string& channel_name) {
    bool is_pending = std::find(pending_channels.begin(), pending_channels.end(), channel_name) != pending_channels.end();
    if (is_pending) {
        return true;
    }

    auto loc = channels.find(channel_name);
    return loc != channels.end() && loc->second.is_subscribed();
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

PusherClient::PusherChannel::PusherChannel(const std::string& name, std::shared_ptr<PusherClient> client)
        : name(name), client(client) {
}

bool PusherClient::PusherChannel::is_subscribed() const {
    return false; // TODO: Implement function.
}

void PusherClient::PusherChannel::bind(const std::string& event_name, ISubscriptionEventListener& listener) {
    // TODO: Implement function.
}

const std::string& PusherClient::PusherChannel::get_name() const {
    return name;
}

}
