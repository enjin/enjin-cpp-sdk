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

#include "enjinsdk/PusherEventService.hpp"

#include "AssetChannel.hpp"
#include "FutureUtils.hpp"
#include "EventTypeDef.hpp"
#include "PlayerChannel.hpp"
#include "ProjectChannel.hpp"
#include "PusherClient.hpp"
#include "PusherEvent.hpp"
#include "PusherEventListener.hpp"
#include "WalletChannel.hpp"
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

using namespace enjin::pusher;
using namespace enjin::sdk::events;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;
using namespace enjin::sdk::websockets;

std::string serialize_pusher_connection_state(PusherConnectionState v) noexcept {
    switch (v) {
        case PusherConnectionState::All:
            return "all";
        case PusherConnectionState::Connecting:
            return "connecting";
        case PusherConnectionState::Connected:
            return "connected";
        case PusherConnectionState::Disconnected:
            return "disconnected";
        case PusherConnectionState::Disconnecting:
            return "disconnecting";
        case PusherConnectionState::Reconnecting:
            return "reconnecting";
        default:
            return "";
    }
}

class PusherEventService::Impl : public IEventService {
public:
    Impl() = delete;

    Impl(std::shared_ptr<PusherEventListener> listener,
         std::unique_ptr<IWebsocketClient> ws_client,
         std::shared_ptr<LoggerProvider> logger_provider)
            : pusher_listener(std::move(listener)),
              ws_client(std::move(ws_client)),
              logger_provider(std::move(logger_provider)) {
    }

    Impl(std::shared_ptr<PusherEventListener> listener,
         std::unique_ptr<IWebsocketClient> ws_client,
         std::shared_ptr<LoggerProvider> logger_provider,
         Platform platform)
            : platform(std::move(platform)),
              pusher_listener(std::move(listener)),
              ws_client(std::move(ws_client)),
              logger_provider(std::move(logger_provider)) {
    }

    ~Impl() override = default;

    std::future<void> start() override {
        shutdown();

        std::optional<Notifications> notifications = platform->get_notifications();
        if (!notifications.has_value()) {
            return create_failed_future("Platform has null data for 'key', 'cluster', or 'encrypted'.");
        }

        std::optional<Pusher> pusher = notifications->get_pusher();
        if (!pusher.has_value() || !pusher->get_options().has_value()) {
            return create_failed_future("Platform has null data for 'key', 'cluster', or 'encrypted'.");
        }

        std::optional<std::string> key = pusher->get_key();
        std::optional<std::string> cluster = pusher->get_options()->get_cluster();
        std::optional<bool> encrypted = pusher->get_options()->get_encrypted();
        if (!key.has_value() || key->empty() || !cluster.has_value() || cluster->empty()) {
            return create_failed_future("Platform has null data for 'key', 'cluster', or 'encrypted'.");
        }

        pusher::PusherOptions options = pusher::PusherOptions()
                .set_cluster(cluster.value())
                .set_encrypted(encrypted.value_or(true));

        client = std::make_unique<PusherClient>(*ws_client, key.value(), options, logger_provider);
        resubscribe_to_channels();

        client->set_on_connection_state_change_handler([this](PusherConnectionState state) {
            if (logger_provider != nullptr && state != PusherConnectionState::All) {
                std::stringstream ss;
                ss << "Pusher client " << serialize_pusher_connection_state(state);

                logger_provider->log(LogLevel::Info, ss.str());
            }

            if (state == PusherConnectionState::Connected && connected_handler.has_value()) {
                connected_handler.value()();
            } else if (state == PusherConnectionState::Disconnected && disconnected_handler.has_value()) {
                disconnected_handler.value()();
            }
        });

        client->set_on_error_handler([this](const std::exception& e) {
            if (logger_provider != nullptr) {
                std::stringstream ss;
                ss << "Error on Pusher client: " << e.what();
                logger_provider->log(LogLevel::Error, ss.str());
            }

            if (error_handler.has_value()) {
                error_handler.value()(e);
            }
        });

        return client->connect();
    }

    std::future<void> start(Platform platform) override {
        Impl::platform = std::move(platform);
        return start();
    }

    std::future<void> shutdown() override {
        if (client == nullptr) {
            return create_failed_future("Event service has not been started.");
        }

        return client->disconnect();
    }

    [[nodiscard]] bool is_connected() const override {
        return client != nullptr && client->get_state() == PusherConnectionState::Connected;
    }

    [[nodiscard]] bool is_registered(const IEventListener& listener) const override {
        auto loc = std::find_if(listeners.begin(), listeners.end(), [&listener](const EventListenerRegistration& r) {
            return &r.get_listener() == &listener;
        });

        return loc != listeners.end();
    }

    void set_connected_handler(std::function<void()> handler) override {
        connected_handler = std::move(handler);
    }

    void set_disconnected_handler(std::function<void()> handler) override {
        disconnected_handler = std::move(handler);
    }

    void set_error_handler(std::function<void(const std::exception&)> handler) override {
        error_handler = std::move(handler);
    }

    const EventListenerRegistration& register_listener(std::shared_ptr<IEventListener> listener) override {
        EventListenerRegistration::RegistrationListenerConfiguration config(std::move(listener));

        return cache_registration(std::move(config));
    }

    const EventListenerRegistration& register_listener_with_matcher(std::shared_ptr<IEventListener> listener,
                                                                    std::function<bool(EventType)> matcher) override {
        EventListenerRegistration::RegistrationListenerConfiguration config(std::move(listener));
        config.with_matcher(std::move(matcher));

        return cache_registration(std::move(config));
    }

    const EventListenerRegistration& register_listener_including_types(std::shared_ptr<IEventListener> listener,
                                                                       std::vector<EventType> types) override {
        EventListenerRegistration::RegistrationListenerConfiguration config(std::move(listener));
        config.with_allowed_events(std::move(types));

        return cache_registration(std::move(config));
    }

    const EventListenerRegistration& register_listener_excluding_types(std::shared_ptr<IEventListener> listener,
                                                                       std::vector<EventType> types) override {
        EventListenerRegistration::RegistrationListenerConfiguration config(std::move(listener));
        config.with_ignored_events(std::move(types));

        return cache_registration(std::move(config));
    }

    void unregister_listener(const IEventListener& listener) override {
        // Finds the first registration that matches
        auto loc = std::find_if(listeners.begin(), listeners.end(), [&listener](const EventListenerRegistration& r) {
            return &r.get_listener() == &listener;
        });

        if (loc != listeners.end()) {
            listeners.erase(loc);
        }
    }

    void subscribe_to_project(std::string project) override {
        subscribe(ProjectChannel(platform.value(), std::move(project)).channel());
    }

    void unsubscribe_to_project(std::string project) override {
        unsubscribe(ProjectChannel(platform.value(), std::move(project)).channel());
    }

    [[nodiscard]] bool is_subscribed_to_project(std::string project) const override {
        return is_subscribed(ProjectChannel(platform.value(), std::move(project)).channel());
    }

    void subscribe_to_player(std::string project, std::string player) override {
        subscribe(PlayerChannel(platform.value(), std::move(project), std::move(player)).channel());
    }

    void unsubscribe_to_player(std::string project, std::string player) override {
        unsubscribe(PlayerChannel(platform.value(), std::move(project), std::move(player)).channel());
    }

    [[nodiscard]] bool is_subscribed_to_player(std::string project, std::string player) const override {
        return is_subscribed(PlayerChannel(platform.value(), std::move(project), std::move(player)).channel());
    }

    void subscribe_to_asset(std::string asset) override {
        subscribe(AssetChannel(platform.value(), std::move(asset)).channel());
    }

    void unsubscribe_to_asset(std::string asset) override {
        unsubscribe(AssetChannel(platform.value(), std::move(asset)).channel());
    }

    [[nodiscard]] bool is_subscribed_to_asset(std::string asset) const override {
        return is_subscribed(AssetChannel(platform.value(), std::move(asset)).channel());
    }

    void subscribe_to_wallet(std::string wallet) override {
        subscribe(WalletChannel(platform.value(), std::move(wallet)).channel());
    }

    void unsubscribe_to_wallet(std::string wallet) override {
        unsubscribe(WalletChannel(platform.value(), std::move(wallet)).channel());
    }

    [[nodiscard]] bool is_subscribed_to_wallet(std::string wallet) const override {
        return is_subscribed(WalletChannel(platform.value(), std::move(wallet)).channel());
    }

    [[nodiscard]] const std::vector<EventListenerRegistration>& get_listeners() const {
        return listeners;
    }

    [[nodiscard]] const std::shared_ptr<LoggerProvider>& get_logger_provider() const {
        return logger_provider;
    }

private:
    std::optional<Platform> platform;
    std::unordered_set<std::string> subscribed_channels;
    std::vector<EventListenerRegistration> listeners;

    std::shared_ptr<PusherEventListener> pusher_listener;
    std::unique_ptr<IWebsocketClient> ws_client;
    std::shared_ptr<LoggerProvider> logger_provider;
    std::unique_ptr<PusherClient> client;

    // Handlers
    std::optional<std::function<void()>> connected_handler;
    std::optional<std::function<void()>> disconnected_handler;
    std::optional<std::function<void(const std::exception&)>> error_handler;

    const EventListenerRegistration&
    cache_registration(EventListenerRegistration::RegistrationListenerConfiguration configuration) {
        // Check if a registration for the listener already exists
        for (const auto& r: listeners) {
            if (&r.get_listener() == &configuration.get_listener()) {
                return r;
            }
        }

        listeners.push_back(configuration.create());

        return listeners.back();
    }

    void subscribe(const std::string& channel) {
        if (client == nullptr || subscribed_channels.find(channel) != subscribed_channels.end()) {
            return;
        }

        subscribed_channels.emplace(channel);
        client->subscribe(channel);
        bind(channel);
    }

    void unsubscribe(const std::string& channel) {
        if (client == nullptr || subscribed_channels.find(channel) == subscribed_channels.end()) {
            return;
        }

        subscribed_channels.erase(channel);
        client->unsubscribe(channel);
    }

    [[nodiscard]] bool is_subscribed(const std::string& channel) const {
        return subscribed_channels.find(channel) != subscribed_channels.end();
    }

    void resubscribe_to_channels() {
        std::unordered_set<std::string> channels(subscribed_channels);
        subscribed_channels.clear();

        for (const auto& channel: channels) {
            subscribe(channel);
        }
    }

    void bind(const std::string& channel) {
        for (auto& def: EventTypeDef::filter_by_channel_type({channel})) {
            client->bind(def.get_key(), pusher_listener);
        }
    }
};

PusherEventService::PusherEventService(std::unique_ptr<IWebsocketClient> ws_client,
                                       std::shared_ptr<LoggerProvider> logger_provider)
        : impl(new Impl(std::make_unique<PusherEventListener>(this),
                        std::move(ws_client),
                        std::move(logger_provider))) {
}

PusherEventService::PusherEventService(std::unique_ptr<IWebsocketClient> ws_client,
                                       std::shared_ptr<LoggerProvider> logger_provider,
                                       Platform platform)
        : impl(new Impl(std::make_unique<PusherEventListener>(this),
                        std::move(ws_client),
                        std::move(logger_provider),
                        std::move(platform))) {
}

PusherEventService::PusherEventService(PusherEventService&& rhs) noexcept: impl(rhs.impl) {
    rhs.impl = nullptr;
}

PusherEventService::~PusherEventService() {
    delete impl;
}

std::future<void> PusherEventService::start() {
    return impl->start();
}

std::future<void> PusherEventService::start(Platform platform) {
    return impl->start(platform);
}

std::future<void> PusherEventService::shutdown() {
    return impl->shutdown();
}

bool PusherEventService::is_connected() const {
    return impl->is_connected();
}

bool PusherEventService::is_registered(const IEventListener& listener) const {
    return impl->is_registered(listener);
}

void PusherEventService::set_connected_handler(std::function<void()> handler) {
    impl->set_connected_handler(handler);
}

void PusherEventService::set_disconnected_handler(std::function<void()> handler) {
    impl->set_disconnected_handler(std::move(handler));
}

void PusherEventService::set_error_handler(std::function<void(const std::exception&)> handler) {
    impl->set_error_handler(std::move(handler));
}

const EventListenerRegistration&
PusherEventService::register_listener(std::shared_ptr<IEventListener> listener) {
    return impl->register_listener(std::move(listener));
}

const EventListenerRegistration&
PusherEventService::register_listener_with_matcher(std::shared_ptr<IEventListener> listener,
                                                   std::function<bool(EventType)> matcher) {
    return impl->register_listener_with_matcher(std::move(listener), std::move(matcher));
}

const EventListenerRegistration&
PusherEventService::register_listener_including_types(std::shared_ptr<IEventListener> listener,
                                                      std::vector<EventType> types) {
    return impl->register_listener_including_types(std::move(listener), std::move(types));
}

const EventListenerRegistration&
PusherEventService::register_listener_excluding_types(std::shared_ptr<IEventListener> listener,
                                                      std::vector<EventType> types) {
    return impl->register_listener_excluding_types(std::move(listener), std::move(types));
}

void PusherEventService::unregister_listener(const IEventListener& listener) {
    impl->unregister_listener(listener);
}

void PusherEventService::subscribe_to_project(std::string project) {
    impl->subscribe_to_project(std::move(project));
}

void PusherEventService::unsubscribe_to_project(std::string project) {
    impl->unsubscribe_to_project(std::move(project));
}

bool PusherEventService::is_subscribed_to_project(std::string project) const {
    return impl->is_subscribed_to_project(std::move(project));
}

void PusherEventService::subscribe_to_player(std::string project, std::string player) {
    impl->subscribe_to_player(std::move(project), std::move(player));
}

void PusherEventService::unsubscribe_to_player(std::string project, std::string player) {
    impl->unsubscribe_to_player(std::move(project), std::move(player));
}

bool PusherEventService::is_subscribed_to_player(std::string project, std::string player) const {
    return impl->is_subscribed_to_player(std::move(project), std::move(player));
}

void PusherEventService::subscribe_to_asset(std::string asset) {
    impl->subscribe_to_asset(std::move(asset));
}

void PusherEventService::unsubscribe_to_asset(std::string asset) {
    impl->unsubscribe_to_asset(std::move(asset));
}

bool PusherEventService::is_subscribed_to_asset(std::string asset) const {
    return impl->is_subscribed_to_asset(std::move(asset));
}

void PusherEventService::subscribe_to_wallet(std::string wallet) {
    impl->subscribe_to_wallet(std::move(wallet));
}

void PusherEventService::unsubscribe_to_wallet(std::string wallet) {
    impl->unsubscribe_to_wallet(std::move(wallet));
}

bool PusherEventService::is_subscribed_to_wallet(std::string wallet) const {
    return impl->is_subscribed_to_wallet(std::move(wallet));
}

const std::vector<EventListenerRegistration>& PusherEventService::get_listeners() const {
    return impl->get_listeners();
}

const std::shared_ptr<LoggerProvider>& PusherEventService::get_logger_provider() const {
    return impl->get_logger_provider();
}

PusherEventService::PusherEventServiceBuilder PusherEventService::builder() {
    return {};
}

PusherEventService PusherEventService::PusherEventServiceBuilder::build() {
    if (m_ws_client == nullptr) {
#if ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL
        m_ws_client = std::make_unique<WebsocketClient>();
#else
        throw std::runtime_error("Attempted building Pusher event service without providing a websocket client");
#endif
    }

    return m_platform.has_value()
           ? PusherEventService(std::move(m_ws_client), std::move(m_logger_provider), m_platform.value())
           : PusherEventService(std::move(m_ws_client), std::move(m_logger_provider));
}

PusherEventService::PusherEventServiceBuilder&
PusherEventService::PusherEventServiceBuilder::platform(Platform platform) {
    m_platform = std::move(platform);
    return *this;
}

PusherEventService::PusherEventServiceBuilder&
PusherEventService::PusherEventServiceBuilder::ws_client(std::unique_ptr<IWebsocketClient> ws_client) {
    m_ws_client = std::move(ws_client);
    return *this;
}

PusherEventService::PusherEventServiceBuilder&
PusherEventService::PusherEventServiceBuilder::logger_provider(std::shared_ptr<LoggerProvider> logger_provider) {
    m_logger_provider = std::move(logger_provider);
    return *this;
}
