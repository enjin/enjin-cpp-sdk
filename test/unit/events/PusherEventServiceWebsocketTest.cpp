#include "gtest/gtest.h"
#include "ProjectChannel.hpp"
#include "PlayerChannel.hpp"
#include "AssetChannel.hpp"
#include "WalletChannel.hpp"
#include "MockWebSocketClientImpl.hpp"
#include "MockWebsocketServer.hpp"
#include "VerificationTestSuite.hpp"
#include "enjinsdk/PusherEventService.hpp"
#include "enjinsdk/internal/pusher/Constants.hpp"
#include <chrono>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace enjin::sdk::events;
using namespace enjin::sdk::models;
using namespace enjin::test::utils;

class PusherEventServiceWebsocketTest : public VerificationTestSuite {
public:
    static constexpr int DEFAULT_PROJECT = 1;
    static constexpr char DEFAULT_PLAYER[] = "player1";
    static constexpr char DEFAULT_TOKEN[] = "0x0";
    static constexpr char DEFAULT_WALLET[] = "0x1";
    static constexpr char PLATFORM_JSON[] =
            R"({"network":"kovan","notifications":{"pusher":{"key":"1","options":{"cluster":"mt1","encrypted":true}}}})";

    MockWebsocketServer mock_server;

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
        std::stringstream ss;
        ss << R"({"event":")"
           << enjin::pusher::Constants::CHANNEL_SUBSCRIPTION_SUCCEEDED
           << R"(","channel":")"
           << channel
           << R"("})";
        return ss.str();
    }

protected:
    void TearDown() override {
        mock_server.close(1000, "Teardown");
    }
};

TEST_F(PusherEventServiceWebsocketTest, StartAndShutdownDoNotThrowExceptions) {
    // Arrange
    auto service = create_default_event_service();

    // Assert
    EXPECT_NO_THROW(service->start());
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    EXPECT_NO_THROW(service->shutdown());
}

TEST_F(PusherEventServiceWebsocketTest, IsConnectedServiceNotStartedReturnsFalse) {
    // Arrange
    auto service = create_default_event_service();

    // Act
    bool actual = service->is_connected();

    // Assert
    EXPECT_FALSE(actual);
}

TEST_F(PusherEventServiceWebsocketTest, IsConnectedServiceStartedAndConnectedToServerReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    bool actual = service->is_connected();

    // Assert
    EXPECT_TRUE(actual);
}

TEST_F(PusherEventServiceWebsocketTest, SubscribeToProjectServiceSubscribesToChannel) {
    // Arrange - Data
    int project = DEFAULT_PROJECT;
    const std::string channel = ProjectChannel(create_default_platform(), project).channel();
    auto service = create_default_event_service();
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
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

TEST_F(PusherEventServiceWebsocketTest, UnsubscribeToProjectServiceIsUnsubscribedFromChannel) {
    // Arrange
    int project = DEFAULT_PROJECT;
    const std::string channel = ProjectChannel(create_default_platform(), project).channel();
    auto service = create_default_event_service();
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
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

TEST_F(PusherEventServiceWebsocketTest, SubscribeToPlayerServiceSubscribesToChannel) {
    // Arrange
    int project = DEFAULT_PROJECT;
    const std::string player(DEFAULT_PLAYER);
    const std::string channel = PlayerChannel(create_default_platform(), project, player).channel();
    auto service = create_default_event_service();
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
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

TEST_F(PusherEventServiceWebsocketTest, UnsubscribeToPlayerServiceIsUnsubscribedFromChannel) {
    // Arrange
    int project = DEFAULT_PROJECT;
    const std::string player(DEFAULT_PLAYER);
    const std::string channel = PlayerChannel(create_default_platform(), project, player).channel();
    auto service = create_default_event_service();
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
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

TEST_F(PusherEventServiceWebsocketTest, SubscribeToTokenServiceSubscribesToChannel) {
    // Arrange
    const std::string token(DEFAULT_TOKEN);
    const std::string channel = AssetChannel(create_default_platform(), token).channel();
    auto service = create_default_event_service();
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
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

TEST_F(PusherEventServiceWebsocketTest, UnsubscribeToTokenServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string token(DEFAULT_TOKEN);
    const std::string channel = AssetChannel(create_default_platform(), token).channel();
    auto service = create_default_event_service();
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
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

TEST_F(PusherEventServiceWebsocketTest, SubscribeToWalletServiceSubscribesToChannel) {
    // Arrange
    const std::string wallet(DEFAULT_WALLET);
    const std::string channel = WalletChannel(create_default_platform(), wallet).channel();
    auto service = create_default_event_service();
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
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

TEST_F(PusherEventServiceWebsocketTest, UnsubscribeToWalletServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string wallet(DEFAULT_WALLET);
    const std::string channel = WalletChannel(create_default_platform(), wallet).channel();
    auto service = create_default_event_service();
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    service->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
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
