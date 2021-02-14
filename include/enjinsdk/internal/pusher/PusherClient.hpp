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

/// \brief Pusher client for subscribing to Pusher channels and binding to events.
class PusherClient {
public:
    PusherClient() = delete;

    /// \brief Constructs a Pusher client with the key and options and uses the websocket client for its connections.
    /// \param ws_client The websocket client.
    /// \param key The application key.
    /// \param options The options.
    PusherClient(std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client,
                 const std::string& key,
                 PusherOptions& options);

    /// \brief Default destructor.
    ~PusherClient() = default;

    /// \brief Connects this client to the server.
    /// \param on_connection_state_change The handler for when the connection state of this client changes.
    /// \param on_error The handler for when this client raises an error.
    /// \return The future for this operation.
    std::future<void> connect(const std::function<void(ConnectionState state)>& on_connection_state_change,
                              const std::function<void(const std::exception& e)>& on_error);

    /// \brief Disconnects this client from the server.
    /// \return The future for this operation.
    std::future<void> disconnect();

    /// \brief Subscribes to the channel to start receiving events for it.
    /// \param channel_name The name of the channel.
    /// \return The future for this operation.
    std::future<void> subscribe(const std::string& channel_name);

    /// \brief Unsubscribes from the channel.
    /// \param channel_name The name of the channel.
    /// \return The future for this operation.
    std::future<void> unsubscribe(const std::string& channel_name);

    /// \brief Determines if this client is already subscribed to or has a pending subscription for the channel.
    /// \param channel_name The name of the channel.
    /// \return Whether there is a subscription or pending subscription.
    bool already_subscribed(const std::string& channel_name);

    /// \brief Binds a listener to the specified event.
    /// \param event_name The name of the event.
    /// \param listener The listener.
    void bind(const std::string& event_name, std::shared_ptr<ISubscriptionEventListener> listener);

    /// \brief Unbinds from the specified event.
    /// \param event_name The name of the event.
    void unbind(const std::string& event_name);

    /// \brief Returns the connection state of this client.
    /// \return The connection state.
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

    void subscription_succeeded(const std::string& channel_name);

    void set_state(ConnectionState state);

    void emit_event(const PusherEvent& event);

    void websocket_message_received(const std::string& message);

    void websocket_closed(int close_status, const std::string& message, const std::error_code& error);
};

}

#endif //ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP
