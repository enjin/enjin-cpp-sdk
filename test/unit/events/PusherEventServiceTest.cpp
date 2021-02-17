#include "gtest/gtest.h"
#include "AppChannel.hpp"
#include "PlayerChannel.hpp"
#include "TokenChannel.hpp"
#include "WalletChannel.hpp"
#include "enjinsdk/PusherEventService.hpp"
#include "enjinsdk/internal/pusher/Constants.hpp"
#include "../../mocks/MockEventListener.hpp"
#include "../../mocks/MockWebSocketClientImpl.hpp"
#include "../../mocks/MockWebsocketServer.hpp"
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <vector>

using namespace enjin::sdk::events;
using namespace enjin::sdk::models;
using namespace enjin::test::utils;

class PusherEventServiceTest : public testing::Test {
public:
    static constexpr int DEFAULT_APP = 1;
    static constexpr char DEFAULT_PLAYER[] = "player1";
    static constexpr char DEFAULT_TOKEN[] = "0x0";
    static constexpr char DEFAULT_WALLET[] = "0x1";
    static constexpr char PLATFORM_JSON[] =
            R"({"network":"kovan","notifications":{"pusher":{"key":"1","options":{"cluster":"mt1","encrypted":true}}}})";

    static constexpr EventType EVENT_TYPES[] = {
            EventType::UNKNOWN,
            EventType::APP_CREATED,
            EventType::APP_DELETED,
            EventType::APP_LINKED,
            EventType::APP_LOCKED,
            EventType::APP_UNLINKED,
            EventType::APP_UNLOCKED,
            EventType::APP_UPDATED,
            EventType::BLOCKCHAIN_LOG_PROCESSED,
            EventType::MESSAGE_PROCESSED,
            EventType::PLAYER_CREATED,
            EventType::PLAYER_DELETED,
            EventType::PLAYER_LINKED,
            EventType::PLAYER_UNLINKED,
            EventType::PLAYER_UPDATED,
            EventType::TOKEN_CREATED,
            EventType::TOKEN_MELTED,
            EventType::TOKEN_MINTED,
            EventType::TOKEN_TRANSFERRED,
            EventType::TOKEN_UPDATED,
            EventType::TRADE_COMPLETED,
            EventType::TRADE_CREATED,
            EventType::TRANSACTION_BROADCAST,
            EventType::TRANSACTION_CANCELED,
            EventType::TRANSACTION_DROPPED,
            EventType::TRANSACTION_EXECUTED,
            EventType::TRANSACTION_FAILED,
            EventType::TRANSACTION_PENDING,
            EventType::TRANSACTION_PROCESSING,
            EventType::TRANSACTION_UPDATED,
    };

    static Platform create_default_platform() {
        Platform platform;
        platform.deserialize(PLATFORM_JSON);
        return platform;
    }

    static std::shared_ptr<PusherEventService> create_default_event_service() {
        return PusherEventServiceBuilder()
                .ws_client(std::make_unique<MockWebSocketClientImpl>())
                .platform(create_default_platform())
                .build();
    }

    static std::string create_subscription_success_message(const std::string& channel = "") {
        return (std::stringstream()
                << R"({"event":")"
                << enjin::pusher::Constants::CHANNEL_SUBSCRIPTION_SUCCEEDED
                << R"(","channel":")"
                << channel
                << R"("})"
        ).str();
    }
};

TEST_F(PusherEventServiceTest, StartAndShutdownDoNotThrowExceptions) {
    // Arrange
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;

    // Assert
    EXPECT_NO_THROW(service->start());
    EXPECT_NO_THROW(service->shutdown());
}

TEST_F(PusherEventServiceTest, IsConnectedServiceNotStartedReturnsFalse) {
    // Arrange
    auto service = create_default_event_service();

    // Act
    bool actual = service->is_connected();

    // Assert
    EXPECT_FALSE(actual);
}

TEST_F(PusherEventServiceTest, IsConnectedServiceStartedAndConnectedToServerReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    service->start();

    // Act
    bool actual = service->is_connected();

    // Assert
    EXPECT_TRUE(actual);

    service->shutdown();
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenNotRegisteredReturnsFalse) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    bool actual = service->is_registered(*listener);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredNormallyReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    service->register_listener(listener);

    // Act
    bool actual = service->is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredWithMatcherReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    std::function<bool(EventType)> matcher;
    service->register_listener_with_matcher(listener, matcher);

    // Act
    bool actual = service->is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredWithIncludingTypesReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    std::vector<EventType> types;
    service->register_listener_including_types(listener, types);

    // Act
    bool actual = service->is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredWithExcludingTypesReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    std::vector<EventType> types;
    service->register_listener_excluding_types(listener, types);

    // Act
    bool actual = service->is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, RegisterListenerRegistrationHasListener) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    auto registration = service->register_listener(listener);

    // Assert
    ASSERT_EQ(listener.get(), &registration.get_listener());
}

TEST_F(PusherEventServiceTest, RegisterListenerWithMatcherRegistrationHasMatcher) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    std::function<bool(EventType)> matcher = [](EventType type) {
        switch (type) {
            case EventType::PLAYER_CREATED:
            case EventType::PLAYER_UPDATED:
            case EventType::TOKEN_TRANSFERRED:
                return true;
            default:
                return false;
        }
    };

    // Act
    auto registration = service->register_listener_with_matcher(listener, matcher);

    // Assert
    for (EventType type : EVENT_TYPES) {
        bool expected = matcher(type);
        bool actual = registration.get_matcher()(type);
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(PusherEventServiceTest, RegisterListenerIncludingTypesRegistrationMatcherIncludesTypes) {
    // Arrange
    auto service = create_default_event_service();
    std::vector<EventType> types = {EventType::PLAYER_CREATED, EventType::PLAYER_UPDATED, EventType::TOKEN_TRANSFERRED};
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    auto registration = service->register_listener_including_types(listener, types);

    // Assert
    for (EventType type : EVENT_TYPES) {
        bool expected = std::find(types.begin(), types.end(), type) != types.end();
        bool actual = registration.get_matcher()(type);
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(PusherEventServiceTest, RegisterListenerExcludingTypesRegistrationMatcherExcludesTypes) {
    // Arrange
    auto service = create_default_event_service();
    std::vector<EventType> types = {EventType::PLAYER_CREATED, EventType::PLAYER_UPDATED, EventType::TOKEN_TRANSFERRED};
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    auto registration = service->register_listener_excluding_types(listener, types);

    // Assert
    for (EventType type : EVENT_TYPES) {
        bool expected = std::find(types.begin(), types.end(), type) == types.end();
        bool actual = registration.get_matcher()(type);
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(PusherEventServiceTest, UnregisterListenerListenerIsUnregestered) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    auto registration = service->register_listener(listener);

    EXPECT_EQ(listener.get(), &registration.get_listener());

    // Act
    service->unregister_listener(*listener);

    // Assert
    ASSERT_FALSE(service->is_registered(*listener));
}

TEST_F(PusherEventServiceTest, UnregisterListenerListenerWasNotUnregesteredDoesNotThrowException) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Assert
    ASSERT_NO_THROW(service->unregister_listener(*listener));
}

TEST_F(PusherEventServiceTest, SubscribeToAppServiceSubscribesToChannel) {
    // Arrange
    int app = DEFAULT_APP;
    const std::string channel = AppChannel(create_default_platform(), app).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    service->start();
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });

    // Act
    service->subscribe_to_app(app);

    // Assert
    EXPECT_TRUE(service->is_subscribed_to_app(app));

    service->shutdown();
}

TEST_F(PusherEventServiceTest, UnsubscribeToAppServiceIsUnsubscribedFromChannel) {
    // Arrange
    int app = DEFAULT_APP;
    const std::string channel = AppChannel(create_default_platform(), app).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    service->start();
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    service->subscribe_to_app(app);

    // Act
    service->unsubscribe_to_app(app);

    // Assert
    EXPECT_FALSE(service->is_subscribed_to_app(app));

    service->shutdown();
}

TEST_F(PusherEventServiceTest, SubscribeToPlayerServiceSubscribesToChannel) {
    // Arrange
    int app = DEFAULT_APP;
    const std::string player(DEFAULT_PLAYER);
    const std::string channel = PlayerChannel(create_default_platform(), app, player).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    service->start();
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });

    // Act
    service->subscribe_to_player(app, player);

    // Assert
    EXPECT_TRUE(service->is_subscribed_to_player(app, player));

    service->shutdown();
}

TEST_F(PusherEventServiceTest, UnsubscribeToPlayerServiceIsUnsubscribedFromChannel) {
    // Arrange
    int app = DEFAULT_APP;
    const std::string player(DEFAULT_PLAYER);
    const std::string channel = PlayerChannel(create_default_platform(), app, player).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    service->start();
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    service->subscribe_to_player(app, player);

    // Act
    service->unsubscribe_to_player(app, player);

    // Assert
    EXPECT_FALSE(service->is_subscribed_to_player(app, player));

    service->shutdown();
}

TEST_F(PusherEventServiceTest, SubscribeToTokenServiceSubscribesToChannel) {
    // Arrange
    const std::string token(DEFAULT_TOKEN);
    const std::string channel = TokenChannel(create_default_platform(), token).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    service->start();
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });

    // Act
    service->subscribe_to_token(token);

    // Assert
    EXPECT_TRUE(service->is_subscribed_to_token(token));

    service->shutdown();
}

TEST_F(PusherEventServiceTest, UnsubscribeToTokenServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string token(DEFAULT_TOKEN);
    const std::string channel = TokenChannel(create_default_platform(), token).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    service->start();
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    service->subscribe_to_token(token);

    // Act
    service->unsubscribe_to_token(token);

    // Assert
    EXPECT_FALSE(service->is_subscribed_to_token(token));

    service->shutdown();
}

TEST_F(PusherEventServiceTest, SubscribeToWalletServiceSubscribesToChannel) {
    // Arrange
    const std::string wallet(DEFAULT_WALLET);
    const std::string channel = WalletChannel(create_default_platform(), wallet).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    service->start();
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });

    // Act
    service->subscribe_to_wallet(wallet);

    // Assert
    EXPECT_TRUE(service->is_subscribed_to_wallet(wallet));

    service->shutdown();
}

TEST_F(PusherEventServiceTest, UnsubscribeToWalletServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string wallet(DEFAULT_WALLET);
    const std::string channel = WalletChannel(create_default_platform(), wallet).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    service->start();
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    service->subscribe_to_wallet(wallet);

    // Act
    service->unsubscribe_to_wallet(wallet);

    // Assert
    EXPECT_FALSE(service->is_subscribed_to_wallet(wallet));

    service->shutdown();
}
