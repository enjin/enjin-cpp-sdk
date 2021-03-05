#include "gtest/gtest.h"
#include "enjinsdk/internal/pusher/PusherClient.hpp"
#include "../../mocks/MockSubscriptionEventListener.hpp"
#include "../../suites/PusherClientTestSuite.hpp"
#include "../../suites/VerificationTestSuite.hpp"
#include <chrono>
#include <exception>
#include <memory>
#include <string>
#include <thread>

using namespace enjin::pusher;
using namespace enjin::sdk;
using namespace enjin::test::utils;

class PusherClientTest : public PusherClientTestSuite,
                         public VerificationTestSuite {
public:
    std::shared_ptr<MockSubscriptionEventListener> mock_listener = std::make_shared<MockSubscriptionEventListener>();

protected:
    void SetUp() override {
        mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
                   .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
                   .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    }
};

TEST_F(PusherClientTest, ConnectClientConnectsToServer) {
    // Arrange
    PusherClient client = create_testable_pusher_client();

    // Assert
    EXPECT_NO_THROW(client.connect());
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    EXPECT_EQ(ConnectionState::CONNECTED, client.get_state());
}

TEST_F(PusherClientTest, DisconnectClientDisconnectsFromServer) {
    // Arrange
    PusherClient client = create_testable_pusher_client();
    client.connect();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    EXPECT_NO_THROW(client.disconnect());
    EXPECT_EQ(ConnectionState::DISCONNECTED, client.get_state());
}

TEST_F(PusherClientTest, SubscribeClientSendsMessageToServerAndSubscribesToChannelAfterReceivingSuccessResponse) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.connect();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this, channel_name](const TestWebsocketMessage& message) {
        increment_call_counter();

        const std::string success_message = create_subscription_success_message(channel_name);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(success_message.begin(), success_message.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    set_expected_call_count(1);

    // Act
    client.subscribe(channel_name).get();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Verify
    verify_call_count(1);

    // Assert
    EXPECT_TRUE(client.is_subscribed(channel_name));
}

TEST_F(PusherClientTest, SubscribeClientSendsMessageToServerAndRaisesErrorAfterReceivingErrorResponse) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.set_on_error_handler([this](const std::exception& e) {
        increment_call_counter();
    });
    client.connect();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();

        const std::string success_message = create_subscription_error_message();
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(success_message.begin(), success_message.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    set_expected_call_count(2);

    // Act
    client.subscribe(channel_name).get();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Verify
    verify_call_count(1);
}

TEST_F(PusherClientTest, UnsubscribeClientSendsMessageToServerAndUnsubscribesFromChannel) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.connect();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mock_server.next_message([this, channel_name](const TestWebsocketMessage& message) {
        const std::string success_message = create_subscription_success_message(channel_name);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(success_message.begin(), success_message.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    client.subscribe(channel_name).get();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    EXPECT_TRUE(client.is_subscribed_or_pending(channel_name));
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
    });
    set_expected_call_count(1);

    // Act
    client.unsubscribe(channel_name);

    // Verify
    verify_call_count(1);

    // Assert
    EXPECT_FALSE(client.is_subscribed_or_pending(channel_name));
}

TEST_F(PusherClientTest, ListenerIsCalledWhenBoundEventIsReceived) {
    // Arrange - Data
    const std::string event_name(DEFAULT_EVENT_NAME);
    const std::string event_message = create_default_event();
    TestWebsocketMessage message;
    PusherClient client = create_testable_pusher_client();
    message.set_data(std::vector<unsigned char>(event_message.begin(), event_message.end()));
    message.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
    client.connect();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    client.bind(event_name, mock_listener);

    // Arrange - Expectations
    EXPECT_CALL(*mock_listener, on_event(testing::An<const PusherEvent&>()))
            .Times(1);

    // Act
    mock_server.send_message(message);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert (see: Arrange - Expectations)
}

TEST_F(PusherClientTest, ListenerIsNotCalledWhenUnboundEventIsReceived) {
    // Arrange - Data
    const std::string event_name(DEFAULT_EVENT_NAME);
    const std::string event_message = create_default_event();
    TestWebsocketMessage message;
    PusherClient client = create_testable_pusher_client();
    message.set_data(std::vector<unsigned char>(event_message.begin(), event_message.end()));
    message.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
    client.connect();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    client.bind(event_name, mock_listener);
    client.unbind(event_name);

    // Arrange - Expectations
    EXPECT_CALL(*mock_listener, on_event(testing::An<const PusherEvent&>()))
            .Times(0);

    // Act
    mock_server.send_message(message);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert (see: Arrange - Expectations)
}
