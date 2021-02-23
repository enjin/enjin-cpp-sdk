#include "gtest/gtest.h"
#include "ProjectChannel.hpp"
#include "PlayerChannel.hpp"
#include "AssetChannel.hpp"
#include "WalletChannel.hpp"
#include "enjinsdk/PusherEventService.hpp"
#include "enjinsdk/internal/pusher/Constants.hpp"
#include "../../mocks/MockEventListener.hpp"
#include "../../mocks/MockWebSocketClientImpl.hpp"
#include "../../mocks/MockWebsocketServer.hpp"
#include "../../suites/VerificationTestSuite.hpp"
#include <algorithm>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace enjin::sdk::events;
using namespace enjin::sdk::models;
using namespace enjin::test::utils;

class PusherEventServiceTest : public VerificationTestSuite {
public:
    static constexpr int DEFAULT_PROJECT = 1;
    static constexpr char DEFAULT_PLAYER[] = "player1";
    static constexpr char DEFAULT_TOKEN[] = "0x0";
    static constexpr char DEFAULT_WALLET[] = "0x1";
    static constexpr char PLATFORM_JSON[] =
            R"({"network":"kovan","notifications":{"pusher":{"key":"1","options":{"cluster":"mt1","encrypted":true}}}})";

    static constexpr EventType EVENT_TYPES[] = {
            EventType::UNKNOWN,
            EventType::PROJECT_CREATED,
            EventType::PROJECT_DELETED,
            EventType::PROJECT_LINKED,
            EventType::PROJECT_LOCKED,
            EventType::PROJECT_UNLINKED,
            EventType::PROJECT_UNLOCKED,
            EventType::PROJECT_UPDATED,
            EventType::BLOCKCHAIN_LOG_PROCESSED,
            EventType::MESSAGE_PROCESSED,
            EventType::PLAYER_CREATED,
            EventType::PLAYER_DELETED,
            EventType::PLAYER_LINKED,
            EventType::PLAYER_UNLINKED,
            EventType::PLAYER_UPDATED,
            EventType::ASSET_CREATED,
            EventType::ASSET_MELTED,
            EventType::ASSET_MINTED,
            EventType::ASSET_TRANSFERRED,
            EventType::ASSET_UPDATED,
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
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    bool actual = service->is_connected();

    // Assert
    EXPECT_TRUE(actual);
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
    std::function < bool(EventType) > matcher;
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
    std::function < bool(EventType) > matcher = [](EventType type) {
        switch (type) {
            case EventType::PLAYER_CREATED:
            case EventType::PLAYER_UPDATED:
            case EventType::ASSET_TRANSFERRED:
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
    std::vector<EventType> types = {EventType::PLAYER_CREATED, EventType::PLAYER_UPDATED, EventType::ASSET_TRANSFERRED};
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
    std::vector<EventType> types = {EventType::PLAYER_CREATED, EventType::PLAYER_UPDATED, EventType::ASSET_TRANSFERRED};
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

TEST_F(PusherEventServiceTest, SubscribeToProjectServiceSubscribesToChannel) {
    // Arrange - Data
    int project = DEFAULT_PROJECT;
    const std::string channel = ProjectChannel(create_default_platform(), project).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this, &mock_server, &channel](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE, message.get_type());

        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    set_expected_call_count(1);

    // Act
    service->subscribe_to_project(project);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Verify
    verify_call_count(2);

    // Assert
    EXPECT_TRUE(service->is_subscribed_to_project(project));
}

TEST_F(PusherEventServiceTest, UnsubscribeToProjectServiceIsUnsubscribedFromChannel) {
    // Arrange
    int project = DEFAULT_PROJECT;
    const std::string channel = ProjectChannel(create_default_platform(), project).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mock_server.next_message([this, &mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    service->subscribe_to_project(project);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    service->unsubscribe_to_project(project);

    // Assert
    EXPECT_FALSE(service->is_subscribed_to_project(project));
}

TEST_F(PusherEventServiceTest, SubscribeToPlayerServiceSubscribesToChannel) {
    // Arrange
    int project = DEFAULT_PROJECT;
    const std::string player(DEFAULT_PLAYER);
    const std::string channel = PlayerChannel(create_default_platform(), project, player).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this, &mock_server, &channel](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE, message.get_type());

        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    set_expected_call_count(1);

    // Act
    service->subscribe_to_player(project, player);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Verify
    verify_call_count(2);

    // Assert
    EXPECT_TRUE(service->is_subscribed_to_player(project, player));
}

TEST_F(PusherEventServiceTest, UnsubscribeToPlayerServiceIsUnsubscribedFromChannel) {
    // Arrange
    int project = DEFAULT_PROJECT;
    const std::string player(DEFAULT_PLAYER);
    const std::string channel = PlayerChannel(create_default_platform(), project, player).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    service->subscribe_to_player(project, player);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    service->unsubscribe_to_player(project, player);

    // Assert
    EXPECT_FALSE(service->is_subscribed_to_player(project, player));
}

TEST_F(PusherEventServiceTest, SubscribeToTokenServiceSubscribesToChannel) {
    // Arrange
    const std::string token(DEFAULT_TOKEN);
    const std::string channel = AssetChannel(create_default_platform(), token).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this, &mock_server, &channel](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE, message.get_type());

        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    set_expected_call_count(1);

    // Act
    service->subscribe_to_asset(token);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Verify
    verify_call_count(2);

    // Assert
    EXPECT_TRUE(service->is_subscribed_to_asset(token));
}

TEST_F(PusherEventServiceTest, UnsubscribeToTokenServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string token(DEFAULT_TOKEN);
    const std::string channel = AssetChannel(create_default_platform(), token).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    service->subscribe_to_asset(token);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    service->unsubscribe_to_asset(token);

    // Assert
    EXPECT_FALSE(service->is_subscribed_to_asset(token));
}

TEST_F(PusherEventServiceTest, SubscribeToWalletServiceSubscribesToChannel) {
    // Arrange
    const std::string wallet(DEFAULT_WALLET);
    const std::string channel = WalletChannel(create_default_platform(), wallet).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this, &mock_server, &channel](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE, message.get_type());

        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    set_expected_call_count(1);

    // Act
    service->subscribe_to_wallet(wallet);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Verify
    verify_call_count(2);

    // Assert
    EXPECT_TRUE(service->is_subscribed_to_wallet(wallet));
}

TEST_F(PusherEventServiceTest, UnsubscribeToWalletServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string wallet(DEFAULT_WALLET);
    const std::string channel = WalletChannel(create_default_platform(), wallet).channel();
    auto service = create_default_event_service();
    MockWebsocketServer mock_server;
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mock_server.next_message([&mock_server, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    service->subscribe_to_wallet(wallet);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    service->unsubscribe_to_wallet(wallet);

    // Assert
    EXPECT_FALSE(service->is_subscribed_to_wallet(wallet));
}
