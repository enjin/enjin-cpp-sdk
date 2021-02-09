#ifndef ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP
#define ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP

#include "enjinsdk/IWebsocketClient.hpp"
#include "enjinsdk/internal/pusher/ConnectionState.hpp"
#include "enjinsdk/internal/pusher/ISubscriptionEventListener.hpp"
#include "enjinsdk/internal/pusher/PusherOptions.hpp"
#include <functional>
#include <future>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <string>

namespace enjin::pusher {

/// \brief TODO
class PusherClient {
public:
    PusherClient() = delete;

    PusherClient(std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client,
                 const std::string& key,
                 PusherOptions& options);

    ~PusherClient() = default;

    std::future<void> connect(const std::function<void(ConnectionState state)>& on_connection_state_change,
                              const std::function<void(const std::exception& e)>& on_error);

    std::future<void> disconnect();

    std::future<void> subscribe(const std::string& channel_name);

    std::future<void> unsubscribe(const std::string& channel_name);

    void subscription_succeeded(const std::string& channel_name);

    void bind(const std::string& event_name, std::shared_ptr<ISubscriptionEventListener> listener);

    void unbind(const std::string& event_name);

    ConnectionState get_state();

private:
    struct PusherChannel {
    public:
        bool is_subscribed = false;
    };

    std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client;
    std::map<std::string, PusherChannel> channels;
    std::set<std::string> pending_channels;
    std::map<std::string, std::vector<std::shared_ptr<ISubscriptionEventListener>>> event_listeners;
    ConnectionState state = ConnectionState::DISCONNECTED;

    std::string key;
    PusherOptions options;

    std::function<void(ConnectionState)> on_connection_state_change;
    std::function<void(const std::exception&)> on_error;

    // Mutex
    std::mutex channels_lock;
    std::mutex event_listeners_lock;
    std::mutex state_lock;

    std::future<void> subscribe_to_channel(const std::string& channel_name);

    bool already_subscribed(const std::string& channel_name);

    void set_state(ConnectionState state);

    void emit_event(const PusherEvent& event);

    void websocket_message_received(const std::string& message);

    void websocket_closed(int close_status, const std::string& message, const std::error_code& error);
};

}

#endif //ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP
