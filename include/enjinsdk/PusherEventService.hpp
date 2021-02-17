#ifndef ENJINCPPSDK_PUSHEREVENTSERVICE_HPP
#define ENJINCPPSDK_PUSHEREVENTSERVICE_HPP

#include "enjinsdk/IEventService.hpp"
#include "enjinsdk/IWebsocketClient.hpp"
#include "enjinsdk/internal/pusher/PusherClient.hpp"
#include "enjinsdk/internal/pusher/PusherEvent.hpp"
#include "enjinsdk/internal/pusher/ISubscriptionEventListener.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::events {

class PusherEventService;

/// \brief Builder for a Pusher event service.
class PusherEventServiceBuilder {
public:
    /// \brief Default constructor.
    PusherEventServiceBuilder() = default;

    /// \brief Default destructor.
    ~PusherEventServiceBuilder() = default;

    /// \brief Builds the event service.
    /// \return The unique pointer for the service.
    std::unique_ptr<PusherEventService> build();

    /// \brief Sets the platform model that the event service will use.
    /// \param platform The platform.
    /// \return This builder for chaining.
    PusherEventServiceBuilder& platform(const models::Platform& platform);

    /// \brief Sets the
    /// \param ws_client The websocket client.
    /// \return This builder for chaining.
    PusherEventServiceBuilder& ws_client(std::unique_ptr<websockets::IWebsocketClient> ws_client);

private:
    std::optional<models::Platform> m_platform;
    std::unique_ptr<websockets::IWebsocketClient> m_ws_client;
};

/// \brief Implementation of IEventService for Pusher events.
class PusherEventService : public IEventService {
private:
    class PusherEventListener : public pusher::ISubscriptionEventListener {
    public:
        PusherEventListener() = delete;

        explicit PusherEventListener(PusherEventService& service);

        ~PusherEventListener() override = default;

        void on_event(const pusher::PusherEvent& event) override;

    private:
        PusherEventService* service;
    };

public:
    PusherEventService() = delete;

    ~PusherEventService() override = default;

    void start() override;

    void start(models::Platform platform) override;

    void shutdown() override;

    bool is_connected() override;

    bool is_registered(IEventListener& listener) override;

    void set_connected_handler(const std::function<void()>& handler) override;

    void set_disconnected_handler(const std::function<void()>& handler) override;

    void set_error_handler(const std::function<void(const std::exception&)>& handler) override;

    EventListenerRegistration register_listener(std::shared_ptr<IEventListener> listener) override;

    EventListenerRegistration
    register_listener_with_matcher(std::shared_ptr<IEventListener> listener,
                                   std::function<bool(models::EventType)> matcher) override;

    EventListenerRegistration
    register_listener_including_types(std::shared_ptr<IEventListener> listener,
                                      const std::vector<models::EventType>& types) override;

    EventListenerRegistration
    register_listener_excluding_types(std::shared_ptr<IEventListener> listener,
                                      const std::vector<models::EventType>& types) override;

    void unregister_listener(IEventListener& listener) override;

    void subscribe_to_app(int app) override;

    void unsubscribe_to_app(int app) override;

    bool is_subscribed_to_app(int app) override;

    void subscribe_to_player(int app, const std::string& player) override;

    void unsubscribe_to_player(int app, const std::string& player) override;

    bool is_subscribed_to_player(int app, const std::string& player) override;

    void subscribe_to_token(const std::string& token) override;

    void unsubscribe_to_token(const std::string& token) override;

    bool is_subscribed_to_token(const std::string& token) override;

    void subscribe_to_wallet(const std::string& wallet) override;

    void unsubscribe_to_wallet(const std::string& wallet) override;

    bool is_subscribed_to_wallet(const std::string& wallet) override;

protected:
    /// \brief The registered listeners for this service.
    std::vector<std::unique_ptr<EventListenerRegistration>> listeners;

    /// \brief Caches the registration created from the configuration.
    /// \param configuration The configuration used to create the registration.
    /// \return Reference to the created registration.
    EventListenerRegistration&
    cache_registration(EventListenerRegistration::RegistrationListenerConfiguration configuration);

private:
    std::shared_ptr<PusherEventListener> listener;
    std::optional<models::Platform> platform;

    std::unique_ptr<pusher::PusherClient> pusher_client;
    std::shared_ptr<websockets::IWebsocketClient> ws_client;

    // Handlers
    std::optional<std::function<void()>> connected_handler;
    std::optional<std::function<void()>> disconnected_handler;
    std::optional<std::function<void(const std::exception&)>> error_handler;

    explicit PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client);

    PusherEventService(std::unique_ptr<websockets::IWebsocketClient> ws_client, models::Platform platform);

    void subscribe(const std::string& channel);

    void unsubscribe(const std::string& channel);

    void bind(const std::string& channel);

    friend std::unique_ptr<PusherEventService> PusherEventServiceBuilder::build();
};

}

#endif //ENJINCPPSDK_PUSHEREVENTSERVICE_HPP
