#ifndef ENJINCPPSDK_PUSHEREVENTSERVICE_HPP
#define ENJINCPPSDK_PUSHEREVENTSERVICE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IEventService.hpp"
#include "enjinsdk/IWebsocketClient.hpp"
#include "enjinsdk/Logger.hpp"
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

    /// \brief Sets the logger.
    /// \param logger The logger.
    /// \return This builder for chaining.
    PusherEventServiceBuilder& logger(std::shared_ptr<utils::Logger> logger);

private:
    std::optional<models::Platform> m_platform;
    std::unique_ptr<websockets::IWebsocketClient> m_ws_client;
    std::shared_ptr<utils::Logger> m_logger;
};

/// \brief Implementation of IEventService for Pusher events.
class ENJINSDK_EXPORT PusherEventService : public IEventService {
public:
    PusherEventService() = delete;

    ~PusherEventService() override;

    void start() override;

    void start(models::Platform platform) override;

    void shutdown() override;

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

    void subscribe_to_project(int project) override;

    void unsubscribe_to_project(int project) override;

    [[nodiscard]] bool is_subscribed_to_project(int project) const override;

    void subscribe_to_player(int project, const std::string& player) override;

    void unsubscribe_to_player(int project, const std::string& player) override;

    [[nodiscard]] bool is_subscribed_to_player(int project, const std::string& player) const override;

    void subscribe_to_asset(const std::string& asset) override;

    void unsubscribe_to_asset(const std::string& asset) override;

    [[nodiscard]] bool is_subscribed_to_asset(const std::string& asset) const override;

    void subscribe_to_wallet(const std::string& wallet) override;

    void unsubscribe_to_wallet(const std::string& wallet) override;

    [[nodiscard]] bool is_subscribed_to_wallet(const std::string& wallet) const override;

protected:
    /// \brief The registered listeners for this service.
    std::vector<std::shared_ptr<EventListenerRegistration>> listeners;

    /// \brief Caches the registration created from the configuration.
    /// \param configuration The configuration used to create the registration.
    /// \return Pointer to the created registration.
    std::shared_ptr<EventListenerRegistration>
    cache_registration(EventListenerRegistration::RegistrationListenerConfiguration configuration);

private:
    class PusherEventListener;

    PusherEventServiceImpl* impl;
    std::shared_ptr<PusherEventListener> listener;

    std::optional<models::Platform> platform;
    std::shared_ptr<utils::Logger> logger;

    explicit PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client,
                                std::shared_ptr<utils::Logger> logger);

    PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client,
                       std::shared_ptr<utils::Logger> logger,
                       models::Platform platform);

    void subscribe(const std::string& channel);

    void unsubscribe(const std::string& channel);

    void bind(const std::string& channel);

    friend std::unique_ptr<PusherEventService> PusherEventServiceBuilder::build();
};

}

#endif //ENJINCPPSDK_PUSHEREVENTSERVICE_HPP
