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

#ifndef ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP
#define ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP

#include "enjinsdk_export.h"
#include "ISubscriptionEventListener.hpp"
#include "ConnectionState.hpp"
#include "PusherOptions.hpp"
#include "enjinsdk/IWebsocketClient.hpp"
#include "enjinsdk/Logger.hpp"
#include <atomic>
#include <exception>
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
class ENJINSDK_EXPORT PusherClient {
public:
    PusherClient() = delete;

    /// \brief Constructs a Pusher client with the key and options and uses the websocket client for its connections.
    /// \param ws_client The websocket client.
    /// \param key The project key.
    /// \param options The options.
    /// \param logger The logger.
    PusherClient(std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client,
                 std::string key,
                 const PusherOptions& options,
                 std::shared_ptr<sdk::utils::Logger> logger = nullptr);

    /// \brief Destructor for client. Attempts to close the websocket client.
    ~PusherClient();

    /// \brief Connects this client to the server.
    void connect();

    /// \brief Disconnects this client from the server.
    void disconnect();

    /// \brief Subscribes to the channel to start receiving events for it.
    /// \param channel_name The name of the channel.
    /// \return The future for this operation.
    std::future<void> subscribe(const std::string& channel_name);

    /// \brief Unsubscribes from the channel.
    /// \param channel_name The name of the channel.
    /// \return The future for this operation.
    std::future<void> unsubscribe(const std::string& channel_name);

    /// \brief Binds a listener to the specified event.
    /// \param event_name The name of the event.
    /// \param listener The listener.
    void bind(const std::string& event_name, std::shared_ptr<ISubscriptionEventListener> listener);

    /// \brief Unbinds from the specified event.
    /// \param event_name The name of the event.
    void unbind(const std::string& event_name);

    /// \brief Determines if this client is already subscribed to or has a pending subscription for the channel.
    /// \param channel_name The name of the channel.
    /// \return Whether there is a subscription or pending subscription.
    [[nodiscard]] bool is_subscribed_or_pending(const std::string& channel_name) const;

    /// \brief Determines if this client is subscribed to the channel.
    /// \param channel_name The name of the channel.
    /// \return Whether this client is subscribed to the channel.
    [[nodiscard]] bool is_subscribed(const std::string& channel_name) const;

    /// \brief Determines if this client has a pending subscription for the channel.
    /// \param channel_name The name of the channel.
    /// \return Whether this client has a pending subscription.
    [[nodiscard]] bool is_subscription_pending(const std::string& channel_name) const;

    /// \brief Returns the connection state of this client.
    /// \return The connection state.
    [[nodiscard]] ConnectionState get_state() const;

    /// \brief Sets the handler for when the connection state changes.
    /// \param handler The handler.
    void set_on_connection_state_change_handler(const std::function<void(ConnectionState)>& handler);

    /// \brief Sets the handler for when errors are received from the server.
    /// \param handler The handler.
    void set_on_error_handler(const std::function<void(const std::exception&)>& handler);

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
    std::shared_ptr<sdk::utils::Logger> logger;

    std::string key;
    PusherOptions options;

    std::optional<std::function<void(ConnectionState)>> on_connection_state_change;
    std::optional<std::function<void(const std::exception&)>> on_error;

    // Mutex
    mutable std::mutex channels_lock;
    mutable std::mutex pending_channels_lock;
    mutable std::mutex event_listeners_lock;
    mutable std::mutex state_lock;

    // Flags
    std::atomic_bool ws_client_closed = true;

    std::future<void> subscribe_to_channel(const std::string& channel_name);

    void subscription_succeeded(const std::string& channel_name);

    void set_state(ConnectionState state);

    void emit_event(const PusherEvent& event);

    void websocket_message_received(const std::string& message);

    void websocket_opened();

    void websocket_closed(int close_status, const std::string& message);
};

}

#endif //ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP
