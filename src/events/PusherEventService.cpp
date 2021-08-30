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

#include "enjinsdk/PusherEventService.hpp"

#include "AssetChannel.hpp"
#include "EnumUtils.hpp"
#include "FutureUtils.hpp"
#include "EventTypeDef.hpp"
#include "PlayerChannel.hpp"
#include "ProjectChannel.hpp"
#include "PusherClient.hpp"
#include "PusherEvent.hpp"
#include "PusherEventListener.hpp"
#include "WalletChannel.hpp"
#include "enjinsdk_utils/StringUtils.hpp"
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <unordered_set>
#include <utility>

#ifndef ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL
#define ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL

#include "WebsocketClient.hpp"

#endif

namespace enjin::sdk::events {

class PusherEventServiceImpl {
public:
    PusherEventServiceImpl() = delete;

    /// \brief Constructs a implementation with the given event listener and websocket client.
    /// \param listener The Pusher event listener.
    /// \param ws_client The websockect client.
    PusherEventServiceImpl(std::unique_ptr<PusherEventListener> listener,
                           std::shared_ptr<websockets::IWebsocketClient> ws_client)
            : listener(std::move(listener)),
              ws_client(std::move(ws_client)),
              client(nullptr) {
    }

    /// \brief Default destructor.
    ~PusherEventServiceImpl() = default;

    /// \brief Initializes and starts a new Pusher client with the given settings.
    /// \param key The application key.
    /// \param options The Pusher options.
    /// \param logger_provider The logger provider to be used by the Pusher client.
    /// \return The future for this operation.
    std::future<void> init_client(const std::string& key,
                                  const pusher::PusherOptions& options,
                                  const std::shared_ptr<utils::LoggerProvider>& logger_provider = nullptr) {
        client = std::make_unique<pusher::PusherClient>(ws_client, key, options, logger_provider);
        resubscribe_to_channels();

        client->set_on_connection_state_change_handler([this, logger_provider](pusher::PusherConnectionState state) {
            if (logger_provider != nullptr && state != pusher::PusherConnectionState::ALL) {
                std::stringstream ss;
                ss << "Pusher client " << enjin::utils::to_lower(utils::serialize_pusher_connection_state(state));
                logger_provider->log(utils::LogLevel::INFO, ss.str());
            }

            if (state == pusher::PusherConnectionState::CONNECTED && connected_handler.has_value()) {
                connected_handler.value()();
            } else if (state == pusher::PusherConnectionState::DISCONNECTED && disconnected_handler.has_value()) {
                disconnected_handler.value()();
            }
        });

        client->set_on_error_handler([this, logger_provider](const std::exception& e) {
            if (logger_provider != nullptr) {
                std::stringstream ss;
                ss << "Error on Pusher client: " << e.what();
                logger_provider->log(utils::LogLevel::SEVERE, ss.str());
            }

            if (error_handler.has_value()) {
                error_handler.value()(e);
            }
        });

        return client->connect();
    }

    /// \brief Disconnects the Pusher client.
    /// \return The future for this operation.
    std::future<void> shutdown() {
        if (client == nullptr) {
            return utils::create_failed_future("Event service has not been started.");
        }

        return client->disconnect();
    }

    /// \brief Determines if the Pusher client is connected to the server.
    /// \return Whether the client is connected to the server.
    [[nodiscard]] bool is_connected() const {
        return client != nullptr && client->get_state() == pusher::PusherConnectionState::CONNECTED;
    }

    /// \brief Sets the handler for when the Pusher client is connected to the server.
    /// \param handler The handler.
    void set_connected_handler(const std::function<void()>& handler) {
        connected_handler = handler;
    }

    /// \brief Sets the handler for when the Pusher client is disconnected from the server.
    /// \param handler The handler.
    void set_disconnected_handler(const std::function<void()>& handler) {
        disconnected_handler = handler;
    }

    /// \brief Sets the handler for when the Pusher client encounters an error.
    /// \param handler The handler.
    void set_error_handler(const std::function<void(const std::exception&)>& handler) {
        error_handler = handler;
    }

    /// \brief Subscribes the Pusher client to the given channel.
    /// \param channel The channel name.
    void subscribe(const std::string& channel) {
        if (client == nullptr || subscribed_channels.find(channel) != subscribed_channels.end()) {
            return;
        }

        subscribed_channels.emplace(channel);
        client->subscribe(channel);
        bind(channel);
    }

    /// \brief Unsubscribes the Pusher client from the given channel.
    /// \param channel The channel name.
    void unsubscribe(const std::string& channel) {
        if (client == nullptr || subscribed_channels.find(channel) == subscribed_channels.end()) {
            return;
        }

        subscribed_channels.erase(channel);
        client->unsubscribe(channel);
    }

    /// \brief Determines if the Pusher client is subscribed to the given channel.
    /// \param channel The channel name.
    /// \return Whether the client is subscribed to the given channel.
    [[nodiscard]] bool is_subscribed(const std::string& channel) const {
        return subscribed_channels.find(channel) != subscribed_channels.end();
    }

private:
    std::unordered_set<std::string> subscribed_channels;

    std::shared_ptr<PusherEventListener> listener;
    std::shared_ptr<websockets::IWebsocketClient> ws_client;
    std::unique_ptr<pusher::PusherClient> client;

    // Handlers
    std::optional<std::function<void()>> connected_handler;
    std::optional<std::function<void()>> disconnected_handler;
    std::optional<std::function<void(const std::exception&)>> error_handler;

    void resubscribe_to_channels() {
        std::unordered_set<std::string> channels(subscribed_channels);
        subscribed_channels.clear();

        for (const auto& channel : channels) {
            subscribe(channel);
        }
    }

    void bind(const std::string& channel) {
        for (auto& def : EventTypeDef::filter_by_channel_type({channel})) {
            client->bind(def.get_key(), listener);
        }
    }
};

PusherEventService::PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client,
                                       std::shared_ptr<utils::LoggerProvider> logger_provider)
        : impl(new PusherEventServiceImpl(std::make_unique<PusherEventListener>(this),
                                          std::move(ws_client))),
          logger_provider(std::move(logger_provider)) {
}

PusherEventService::PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client,
                                       std::shared_ptr<utils::LoggerProvider> logger_provider,
                                       models::Platform platform)
        : impl(new PusherEventServiceImpl(std::make_unique<PusherEventListener>(this),
                                          std::move(ws_client))),
          platform(std::move(platform)),
          logger_provider(std::move(logger_provider)) {
}

PusherEventService::~PusherEventService() {
    delete impl;
}

std::future<void> PusherEventService::start() {
    shutdown();

    std::optional<models::Notifications> notifications = platform->get_notifications();
    if (!notifications.has_value()) {
        return utils::create_failed_future("Platform has null data for 'key', 'cluster', or 'encrypted'.");
    }

    std::optional<models::Pusher> pusher = notifications->get_pusher();
    if (!pusher.has_value() || !pusher->get_options().has_value()) {
        return utils::create_failed_future("Platform has null data for 'key', 'cluster', or 'encrypted'.");
    }

    std::optional<std::string> key = pusher->get_key();
    std::optional<std::string> cluster = pusher->get_options()->get_cluster();
    std::optional<bool> encrypted = pusher->get_options()->get_encrypted();
    if (!key.has_value() || key->empty() || !cluster.has_value() || cluster->empty()) {
        return utils::create_failed_future("Platform has null data for 'key', 'cluster', or 'encrypted'.");
    }

    pusher::PusherOptions options = pusher::PusherOptions()
            .set_cluster(cluster.value())
            .set_encrypted(encrypted.value_or(true));

    return impl->init_client(key.value(), options, logger_provider);
}

std::future<void> PusherEventService::start(models::Platform platform) {
    PusherEventService::platform = std::move(platform);
    return start();
}

std::future<void> PusherEventService::shutdown() {
    return impl->shutdown();
}

bool PusherEventService::is_connected() const {
    return impl->is_connected();
}

bool PusherEventService::is_registered(IEventListener& listener) const {
    auto loc = std::find_if(listeners.begin(),
                            listeners.end(),
                            [&listener](const std::shared_ptr<EventListenerRegistration>& r) {
                                return &r->get_listener() == &listener;
                            });
    return loc != listeners.end();
}

void PusherEventService::set_connected_handler(const std::function<void()>& handler) {
    impl->set_connected_handler(handler);
}

void PusherEventService::set_disconnected_handler(const std::function<void()>& handler) {
    impl->set_disconnected_handler(handler);
}

void PusherEventService::set_error_handler(const std::function<void(const std::exception&)>& handler) {
    impl->set_error_handler(handler);
}

std::shared_ptr<EventListenerRegistration>
PusherEventService::register_listener(std::shared_ptr<IEventListener> listener) {
    return cache_registration(EventListenerRegistration::RegistrationListenerConfiguration(listener));
}

std::shared_ptr<EventListenerRegistration>
PusherEventService::register_listener_with_matcher(std::shared_ptr<IEventListener> listener,
                                                   std::function<bool(models::EventType)> matcher) {
    return cache_registration(EventListenerRegistration::RegistrationListenerConfiguration(listener)
                                      .with_matcher(matcher));
}

std::shared_ptr<EventListenerRegistration>
PusherEventService::register_listener_including_types(std::shared_ptr<IEventListener> listener,
                                                      const std::vector<models::EventType>& types) {
    return cache_registration(EventListenerRegistration::RegistrationListenerConfiguration(listener)
                                      .with_allowed_events(types));
}

std::shared_ptr<EventListenerRegistration>
PusherEventService::register_listener_excluding_types(std::shared_ptr<IEventListener> listener,
                                                      const std::vector<models::EventType>& types) {
    return cache_registration(EventListenerRegistration::RegistrationListenerConfiguration(listener)
                                      .with_ignored_events(types));
}

std::shared_ptr<EventListenerRegistration>
PusherEventService::cache_registration(EventListenerRegistration::RegistrationListenerConfiguration configuration) {
    // Check if a registration for the listener already exists
    for (const auto& r : listeners) {
        if (&r->get_listener() == &configuration.get_listener()) {
            return r;
        }
    }

    std::shared_ptr<EventListenerRegistration> registration = configuration.create();
    listeners.push_back(registration);

    return registration;
}

void PusherEventService::unregister_listener(IEventListener& listener) {
    // Finds the first registration that matches
    auto loc = std::find_if(listeners.begin(),
                            listeners.end(),
                            [&listener](const std::shared_ptr<EventListenerRegistration>& r) {
                                return &r->get_listener() == &listener;
                            });

    if (loc != listeners.end()) {
        listeners.erase(loc);
    }
}

void PusherEventService::subscribe_to_project(const std::string& project) {
    impl->subscribe(ProjectChannel(platform.value(), project).channel());
}

void PusherEventService::unsubscribe_to_project(const std::string& project) {
    impl->unsubscribe(ProjectChannel(platform.value(), project).channel());
}

bool PusherEventService::is_subscribed_to_project(const std::string& project) const {
    return impl->is_subscribed(ProjectChannel(platform.value(), project).channel());
}

void PusherEventService::subscribe_to_player(const std::string& project, const std::string& player) {
    impl->subscribe(PlayerChannel(platform.value(), project, player).channel());
}

void PusherEventService::unsubscribe_to_player(const std::string& project, const std::string& player) {
    impl->unsubscribe(PlayerChannel(platform.value(), project, player).channel());
}

bool PusherEventService::is_subscribed_to_player(const std::string& project, const std::string& player) const {
    return impl->is_subscribed(PlayerChannel(platform.value(), project, player).channel());
}

void PusherEventService::subscribe_to_asset(const std::string& asset) {
    impl->subscribe(AssetChannel(platform.value(), asset).channel());
}

void PusherEventService::unsubscribe_to_asset(const std::string& asset) {
    impl->unsubscribe(AssetChannel(platform.value(), asset).channel());
}

bool PusherEventService::is_subscribed_to_asset(const std::string& asset) const {
    return impl->is_subscribed(AssetChannel(platform.value(), asset).channel());
}

void PusherEventService::subscribe_to_wallet(const std::string& wallet) {
    impl->subscribe(WalletChannel(platform.value(), wallet).channel());
}

void PusherEventService::unsubscribe_to_wallet(const std::string& wallet) {
    impl->unsubscribe(WalletChannel(platform.value(), wallet).channel());
}

bool PusherEventService::is_subscribed_to_wallet(const std::string& wallet) const {
    return impl->is_subscribed(WalletChannel(platform.value(), wallet).channel());
}

const std::vector<std::shared_ptr<EventListenerRegistration>>& PusherEventService::get_listeners() const {
    return listeners;
}

const std::shared_ptr<utils::LoggerProvider>& PusherEventService::get_logger_provider() const {
    return logger_provider;
}

std::unique_ptr<PusherEventService> PusherEventServiceBuilder::build() {
    if (m_ws_client == nullptr) {
#if ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL
        m_ws_client = std::make_unique<websockets::WebsocketClient>();
#else
        throw std::runtime_error("Attempted building Pusher event service without providing a websocket client");
#endif
    }

    return m_platform.has_value()
           ? std::unique_ptr<PusherEventService>(new PusherEventService(std::move(m_ws_client),
                                                                        m_provider,
                                                                        m_platform.value()))
           : std::unique_ptr<PusherEventService>(new PusherEventService(std::move(m_ws_client),
                                                                        m_provider));
}

PusherEventServiceBuilder& PusherEventServiceBuilder::platform(const models::Platform& platform) {
    m_platform = platform;
    return *this;
}

PusherEventServiceBuilder&
PusherEventServiceBuilder::ws_client(std::unique_ptr<websockets::IWebsocketClient> ws_client) {
    m_ws_client = std::move(ws_client);
    return *this;
}

PusherEventServiceBuilder& PusherEventServiceBuilder::logger_provider(std::shared_ptr<utils::LoggerProvider> provider) {
    m_provider = std::move(provider);
    return *this;
}

}
