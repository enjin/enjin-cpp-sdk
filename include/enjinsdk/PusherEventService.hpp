/* Copyright 2021 Enjin Pte. Ltd.
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

/// \brief Implementation of IEventService for Pusher events.
class ENJINSDK_EXPORT PusherEventService : public IEventService {
public:
    class PusherEventServiceBuilder;

    PusherEventService() = delete;

    PusherEventService(const PusherEventService&) = delete;

    PusherEventService(PusherEventService&& rhs) = delete;

    ~PusherEventService() override;

    std::future<void> start() override;

    std::future<void> start(models::Platform platform) override;

    std::future<void> shutdown() override;

    [[nodiscard]] bool is_connected() const override;

    [[nodiscard]] bool is_registered(const IEventListener& listener) const override;

    void set_connected_handler(std::function<void()> handler) override;

    void set_disconnected_handler(std::function<void()> handler) override;

    void set_error_handler(std::function<void(const std::exception&)> handler) override;

    const EventListenerRegistration& register_listener(std::shared_ptr<IEventListener> listener) override;

    const EventListenerRegistration&
    register_listener_with_matcher(std::shared_ptr<IEventListener> listener,
                                   std::function<bool(models::EventType)> matcher) override;

    const EventListenerRegistration&
    register_listener_including_types(std::shared_ptr<IEventListener> listener,
                                      std::vector<models::EventType> types) override;

    const EventListenerRegistration&
    register_listener_excluding_types(std::shared_ptr<IEventListener> listener,
                                      std::vector<models::EventType> types) override;

    void unregister_listener(const IEventListener& listener) override;

    void subscribe_to_project(std::string project) override;

    void unsubscribe_to_project(std::string project) override;

    [[nodiscard]] bool is_subscribed_to_project(std::string project) const override;

    void subscribe_to_player(std::string project, std::string player) override;

    void unsubscribe_to_player(std::string project, std::string player) override;

    [[nodiscard]] bool is_subscribed_to_player(std::string project, std::string player) const override;

    void subscribe_to_asset(std::string asset) override;

    void unsubscribe_to_asset(std::string asset) override;

    [[nodiscard]] bool is_subscribed_to_asset(std::string asset) const override;

    void subscribe_to_wallet(std::string wallet) override;

    void unsubscribe_to_wallet(std::string wallet) override;

    [[nodiscard]] bool is_subscribed_to_wallet(std::string wallet) const override;

    /// \brief Returns the registrations for listeners registered to this service.
    /// \return The listener registrations.
    [[nodiscard]] const std::vector<EventListenerRegistration>& get_listeners() const;

    /// \brief Returns the logger provider used by this service.
    /// \return The logger provider.
    [[nodiscard]] const std::shared_ptr<utils::LoggerProvider>& get_logger_provider() const;

    /// \brief Creates a builder for this class.
    /// \return The builder.
    [[nodiscard]] static PusherEventServiceBuilder builder();

    /// \brief Builder class for PusherEventService.
    class ENJINSDK_EXPORT PusherEventServiceBuilder {
    public:
        /// \brief Default destructor.
        ~PusherEventServiceBuilder() = default;

        /// \brief Builds the event service.
        /// \return The service.
        [[nodiscard]] std::unique_ptr<PusherEventService> build();

        /// \brief Sets the platform model that the event service will use.
        /// \param platform The platform.
        /// \return This builder for chaining.
        PusherEventServiceBuilder& platform(models::Platform platform);

        /// \brief Sets the websocket client to be moved to the service.
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
        std::shared_ptr<utils::LoggerProvider> m_logger_provider;

        PusherEventServiceBuilder() = default;

        friend PusherEventServiceBuilder PusherEventService::builder();
    };

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;

    explicit PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client,
                                std::shared_ptr<utils::LoggerProvider> logger_provider);

    PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client,
                       std::shared_ptr<utils::LoggerProvider> logger_provider,
                       models::Platform platform);
};

}

#endif //ENJINCPPSDK_PUSHEREVENTSERVICE_HPP
