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

#ifndef ENJINCPPSDK_PUSHEREVENTSERVICE_HPP
#define ENJINCPPSDK_PUSHEREVENTSERVICE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IEventService.hpp"
#include "enjinsdk/IWebsocketClient.hpp"
#include "enjinsdk/LoggerProvider.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::events {

/// \brief Implementation of the Pusher event service used internally.
class ENJINSDK_EXPORT PusherEventServiceImpl;

class PusherEventService;

/// \brief Builder for a Pusher event service.
class ENJINSDK_EXPORT PusherEventServiceBuilder {
public:
    /// \brief Default constructor.
    PusherEventServiceBuilder() = default;

    /// \brief Default destructor.
    ~PusherEventServiceBuilder() = default;

    /// \brief Builds the event service.
    /// \return The unique pointer for the service.
    [[nodiscard]] std::unique_ptr<PusherEventService> build();

    /// \brief Sets the platform model that the event service will use.
    /// \param platform The platform.
    /// \return This builder for chaining.
    PusherEventServiceBuilder& platform(const models::Platform& platform);

    /// \brief Sets the websocket client.
    /// \param ws_client The websocket client.
    /// \return This builder for chaining.
    PusherEventServiceBuilder& ws_client(std::unique_ptr<websockets::IWebsocketClient> ws_client);

    /// \brief Sets the logger provider to be used by the event service.
    /// \param logger_provider The logger provider.
    /// \return This builder for chaining.
    PusherEventServiceBuilder& logger_provider(std::shared_ptr<utils::LoggerProvider> logger_provider);

private:
    std::optional<models::Platform> m_platform;
    std::unique_ptr<websockets::IWebsocketClient> m_ws_client;
    std::shared_ptr<utils::LoggerProvider> m_provider;
};

/// \brief Implementation of IEventService for Pusher events.
class ENJINSDK_EXPORT PusherEventService : public IEventService {
public:
    PusherEventService() = delete;

    ~PusherEventService() override;

    std::future<void> start() override;

    std::future<void> start(models::Platform platform) override;

    std::future<void> shutdown() override;

    [[nodiscard]] bool is_connected() const override;

    [[nodiscard]] bool is_registered(IEventListener& listener) const override;

    void set_connected_handler(const std::function<void()>& handler) override;

    void set_disconnected_handler(const std::function<void()>& handler) override;

    void set_error_handler(const std::function<void(const std::exception&)>& handler) override;

    std::shared_ptr<EventListenerRegistration> register_listener(std::shared_ptr<IEventListener> listener) override;

    std::shared_ptr<EventListenerRegistration>
    register_listener_with_matcher(std::shared_ptr<IEventListener> listener,
                                   std::function<bool(models::EventType)> matcher) override;

    std::shared_ptr<EventListenerRegistration>
    register_listener_including_types(std::shared_ptr<IEventListener> listener,
                                      const std::vector<models::EventType>& types) override;

    std::shared_ptr<EventListenerRegistration>
    register_listener_excluding_types(std::shared_ptr<IEventListener> listener,
                                      const std::vector<models::EventType>& types) override;

    void unregister_listener(IEventListener& listener) override;

    /// \brief Opens a channel for the specified project, allowing listeners to receive events for it.
    /// \param project The project's UUID.
    /// \remarks This operation may timeout after 30 seconds if no response is received from the server. In such event,
    /// this service will unsubscribe from the given channel.
    void subscribe_to_project(const std::string& project) override;

    void unsubscribe_to_project(const std::string& project) override;

    [[nodiscard]] bool is_subscribed_to_project(const std::string& project) const override;

    /// \brief Opens a channel for the specified player, allowing listeners to receive events for it.
    /// \param project The project's UUID.
    /// \param player The player ID.
    /// \remarks This operation may timeout after 30 seconds if no response is received from the server. In such event,
    /// this service will unsubscribe from the given channel.
    void subscribe_to_player(const std::string& project, const std::string& player) override;

    void unsubscribe_to_player(const std::string& project, const std::string& player) override;

    [[nodiscard]] bool is_subscribed_to_player(const std::string& project, const std::string& player) const override;

    /// \brief Opens a channel for the specified asset, allowing listeners to receive events for it.
    /// \param asset The asset ID.
    /// \remarks This operation may timeout after 30 seconds if no response is received from the server. In such event,
    /// this service will unsubscribe from the given channel.
    void subscribe_to_asset(const std::string& asset) override;

    void unsubscribe_to_asset(const std::string& asset) override;

    [[nodiscard]] bool is_subscribed_to_asset(const std::string& asset) const override;

    /// \brief Opens a channel for the specified wallet, allowing listeners to receive events for it.
    /// \param wallet The wallet's address.
    /// \remarks This operation may timeout after 30 seconds if no response is received from the server. In such event,
    /// this service will unsubscribe from the given channel.
    void subscribe_to_wallet(const std::string& wallet) override;

    void unsubscribe_to_wallet(const std::string& wallet) override;

    [[nodiscard]] bool is_subscribed_to_wallet(const std::string& wallet) const override;

    /// \brief Returns the registrations for listeners registered to this service.
    /// \return The listener registrations.
    [[nodiscard]] const std::vector<std::shared_ptr<EventListenerRegistration>>& get_listeners() const;

    /// \brief Returns the logger provider used by this service.
    /// \return The logger provider.
    [[nodiscard]] const std::shared_ptr<utils::LoggerProvider>& get_logger_provider() const;

protected:
    /// \brief The registered listeners for this service.
    std::vector<std::shared_ptr<EventListenerRegistration>> listeners;

    /// \brief Caches the registration created from the configuration.
    /// \param configuration The configuration used to create the registration.
    /// \return Pointer to the created registration.
    std::shared_ptr<EventListenerRegistration>
    cache_registration(EventListenerRegistration::RegistrationListenerConfiguration configuration);

private:
    PusherEventServiceImpl* impl;

    std::optional<models::Platform> platform;
    std::shared_ptr<utils::LoggerProvider> logger_provider;

    explicit PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client,
                                std::shared_ptr<utils::LoggerProvider> logger_provider);

    PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client,
                       std::shared_ptr<utils::LoggerProvider> logger,
                       models::Platform platform);

    friend std::unique_ptr<PusherEventService> PusherEventServiceBuilder::build();
};

}

#endif //ENJINCPPSDK_PUSHEREVENTSERVICE_HPP
