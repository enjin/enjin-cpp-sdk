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

#ifndef ENJINCPPSDK_IEVENTSERVICE_HPP
#define ENJINCPPSDK_IEVENTSERVICE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/EventListenerRegistration.hpp"
#include "enjinsdk/models/Platform.hpp"
#include <functional>
#include <future>
#include <memory>
#include <string>
#include <vector>

namespace enjin::sdk::events {

/// \brief Event service interface for subscribing to and registering for events from the Enjin Cloud.
class ENJINSDK_EXPORT IEventService {
public:
    /// \brief Default destructor.
    virtual ~IEventService() = default;

    /// \brief Starts this service.
    /// \return The future for this operation.
    virtual std::future<void> start() = 0;

    /// \brief Starts this service with the provided platform details.
    /// \param platform The platform details.
    /// \return The future for this operation.
    virtual std::future<void> start(const models::Platform& platform) = 0;

    /// \brief Shuts down this service.
    /// \return The future for this operation.
    virtual std::future<void> shutdown() = 0;

    /// \brief Determines if this service is connected for receiving events.
    /// \return Whether this service is connected.
    [[nodiscard]] virtual bool is_connected() const = 0;

    /// \brief Determines if the the listener is registered to this service.
    /// \param listener The listener.
    /// \return Whether the listener is registered.
    [[nodiscard]] virtual bool is_registered(const IEventListener& listener) const = 0;

    /// \brief Sets a handler for when the service connects to the server.
    /// \param handler The handler.
    virtual void set_connected_handler(const std::function<void()>& handler) = 0;

    /// \brief Sets a handler for when the service disconnects from the server.
    /// \param handler The handler.
    virtual void set_disconnected_handler(const std::function<void()>& handler) = 0;

    /// \brief Sets a handler for when the service encounters an error.
    /// \param handler The handler.
    virtual void set_error_handler(const std::function<void(const std::exception& e)>& handler) = 0;

    /// \brief Registers a event listener and provides the registration for it.
    /// \param listener The listener.
    /// \return The registration.
    virtual const EventListenerRegistration&
    register_listener(const std::shared_ptr<IEventListener>& listener) = 0;

    /// \brief Registers a event listener with a function for event matcher and provides the registration for it.
    /// \param listener The listener.
    /// \param matcher The event matcher.
    /// \return The registration.
    virtual const EventListenerRegistration&
    register_listener_with_matcher(const std::shared_ptr<IEventListener>& listener,
                                   const std::function<bool(models::EventType)>& matcher) = 0;

    /// \brief Registers a event listener with event types to allow and provides the registration for it.
    /// \param listener The listener.
    /// \param types The event types to allow.
    /// \return The registration.
    virtual const EventListenerRegistration&
    register_listener_including_types(const std::shared_ptr<IEventListener>& listener,
                                      const std::vector<models::EventType>& types) = 0;

    /// \brief Registers a event listener with event types to ignore and provides the registration for it.
    /// \param listener The listener.
    /// \param types The event types to ignore.
    /// \return The registration.
    virtual const EventListenerRegistration&
    register_listener_excluding_types(const std::shared_ptr<IEventListener>& listener,
                                      const std::vector<models::EventType>& types) = 0;

    /// \brief Unregisters the event listener from this service.
    /// \param listener The listener.
    virtual void unregister_listener(const IEventListener& listener) = 0;

    /// \brief Opens a channel for the specified project, allowing listeners to receive events for it.
    /// \param project The project's UUID.
    virtual void subscribe_to_project(const std::string& project) = 0;

    /// \brief Closes a channel for the specified project, preventing listeners from receiving events for it.
    /// \param project The project's UUID.
    virtual void unsubscribe_to_project(const std::string& project) = 0;

    /// \brief Determines if this service is subscribed to the specified channel.
    /// \param project The project's UUID.
    /// \return Whether this service is subscribed to the channel.
    [[nodiscard]] virtual bool is_subscribed_to_project(const std::string& project) const = 0;

    /// \brief Opens a channel for the specified player, allowing listeners to receive events for it.
    /// \param project The project's UUID.
    /// \param player The player ID.
    virtual void subscribe_to_player(const std::string& project, const std::string& player) = 0;

    /// \brief Closes a channel for the specified player, preventing listeners from receiving events for it.
    /// \param project The project's UUID.
    /// \param player The player ID.
    virtual void unsubscribe_to_player(const std::string& project, const std::string& player) = 0;

    /// \brief Determines if this service is subscribed to the specified channel.
    /// \param project The project's UUID.
    /// \param player The player ID.
    /// \return Whether this service is subscribed to the channel.
    [[nodiscard]] virtual bool is_subscribed_to_player(const std::string& project, const std::string& player) const = 0;

    /// \brief Opens a channel for the specified asset, allowing listeners to receive events for it.
    /// \param asset The asset ID.
    virtual void subscribe_to_asset(const std::string& asset) = 0;

    /// \brief Closes a channel for the specified asset, preventing listeners from receiving events for it.
    /// \param asset The asset ID.
    virtual void unsubscribe_to_asset(const std::string& asset) = 0;

    /// \brief Determines if this service is subscribed to the specified channel.
    /// \param asset The asset ID.
    /// \return Whether this service is subscribed to the channel.
    [[nodiscard]] virtual bool is_subscribed_to_asset(const std::string& asset) const = 0;

    /// \brief Opens a channel for the specified wallet, allowing listeners to receive events for it.
    /// \param wallet The wallet's address.
    virtual void subscribe_to_wallet(const std::string& wallet) = 0;

    /// \brief Closes a channel for the specified wallet, preventing listeners from receiving events for it.
    /// \param wallet The wallet's address.
    virtual void unsubscribe_to_wallet(const std::string& wallet) = 0;

    /// \brief Determines if this service is subscribed to the specified channel.
    /// \param wallet The address.
    /// \return Whether this service is subscribed to the channel.
    [[nodiscard]] virtual bool is_subscribed_to_wallet(const std::string& wallet) const = 0;
};

}

#endif //ENJINCPPSDK_IEVENTSERVICE_HPP
