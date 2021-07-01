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

#include "gtest/gtest.h"
#include "MockSubscriptionEventListener.hpp"
#include "PusherClientTestSuite.hpp"
#include "VerificationTestSuite.hpp"
#include <chrono>
#include <exception>
#include <future>
#include <memory>
#include <string>
#include <thread>

using namespace enjin::pusher;
using namespace enjin::sdk;
using namespace enjin::test::mocks;
using namespace enjin::test::suites;

class PusherClientTest : public PusherClientTestSuite,
                         public VerificationTestSuite,
                         public testing::Test {
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

    // Act
    std::future<void> future = client.connect();

    // Assert
    EXPECT_NO_THROW(future.get());
    EXPECT_EQ(PusherConnectionState::CONNECTED, client.get_state());
}

TEST_F(PusherClientTest, DisconnectClientDisconnectsFromServer) {
    // Arrange
    PusherClient client = create_testable_pusher_client();
    client.connect().get();

    // Assert
    EXPECT_NO_THROW(client.disconnect().get());
    EXPECT_EQ(PusherConnectionState::DISCONNECTED, client.get_state());
}

TEST_F(PusherClientTest, SubscribeClientSendsMessageToServerAndSubscribesToChannelAfterReceivingSuccessResponse) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.connect().get();

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

    // Assert
    ASSERT_TRUE(client.is_subscribed(channel_name));

    // Verify
    verify_call_count(1);
}

TEST_F(PusherClientTest, SubscribeFutureCompletesExceptionallyOnTimeout) {
    // Arrange
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherOptions options = PusherOptions()
            .set_cluster(DEFAULT_CLUSTER)
            .set_client_timeout(std::chrono::seconds(0)); // Ensures timeout finishes immediately
    PusherClient client = PusherClient(mock_ws_client, DEFAULT_KEY, options);
    client.connect().get();

    // Act
    std::future<void> future = client.subscribe(channel_name);

    // Assert
    ASSERT_ANY_THROW(future.get());
}

TEST_F(PusherClientTest, UnsubscribeClientSendsMessageToServerAndUnsubscribesFromChannel) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.connect().get();
    mock_server.next_message([this, channel_name](const TestWebsocketMessage& message) {
        const std::string success_message = create_subscription_success_message(channel_name);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(success_message.begin(), success_message.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    client.subscribe(channel_name).get();

    // Arrange - Expectations
    EXPECT_TRUE(client.is_subscribed(channel_name));
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
    });
    set_expected_call_count(1);

    // Act
    client.unsubscribe(channel_name).get();

    // Assert
    ASSERT_FALSE(client.is_subscribed(channel_name));

    // Verify
    verify_call_count(1);
}

TEST_F(PusherClientTest, UnsubscribeClientUnsubscribesWhilePendingSubscription) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherOptions options = PusherOptions()
            .set_cluster(DEFAULT_CLUSTER)
            .set_client_timeout(std::chrono::seconds(5)); // Ensures timeout does not expire during test
    PusherClient client = PusherClient(mock_ws_client, DEFAULT_KEY, options);
    client.connect().get();
    mock_server.next_message([this, channel_name](const TestWebsocketMessage& message) {
        const std::string success_message = create_subscription_success_message(channel_name);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(success_message.begin(), success_message.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    std::future<void> future = client.subscribe(channel_name);

    // Arrange - Expectations
    EXPECT_TRUE(future.valid());
    EXPECT_TRUE(client.is_subscription_pending(channel_name));
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
    });
    set_expected_call_count(1);

    // Act
    client.unsubscribe(channel_name).get();

    // Assert
    EXPECT_EQ(std::future_status::ready, future.wait_for(std::chrono::seconds(0)));
    EXPECT_NO_THROW(future.get());
    EXPECT_FALSE(client.is_subscribed_or_pending(channel_name));

    // Verify
    verify_call_count(1);
}

TEST_F(PusherClientTest, ListenerIsCalledWhenBoundEventIsReceived) {
    // Arrange - Data
    const std::string event_name(DEFAULT_EVENT_NAME);
    const std::string event_message = create_default_event();
    TestWebsocketMessage message;
    PusherClient client = create_testable_pusher_client();
    message.set_data(std::vector<unsigned char>(event_message.begin(), event_message.end()));
    message.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
    client.connect().get();
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
    client.connect().get();
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

TEST_F(PusherClientTest, ClientSendsCachedSubscribeMessageAfterConnecting) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.subscribe(channel_name).get();

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
    client.connect().get();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    ASSERT_TRUE(client.is_subscribed(channel_name));

    // Verify
    verify_call_count(1);
}

TEST_F(PusherClientTest, ClientUncachesAndDoesNotSendSubscribeMessageAfterConnecting) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.subscribe(channel_name).get();
    client.unsubscribe(channel_name).get();

    // Arrange - Expectations
    mock_server.next_message([this, channel_name](const TestWebsocketMessage& message) {
        increment_call_counter();
    });
    set_expected_call_count(0);

    // Act
    client.connect().get();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    ASSERT_FALSE(client.is_subscribed(channel_name));

    // Verify
    verify_call_count(1);
}

TEST_F(PusherClientTest, ClientReceivesErrorMessageFromServerAndRaisesExceptionInHandler) {
    // Arrange - Data
    const std::string error_message = create_subscription_error_message();
    PusherClient client = create_testable_pusher_client();
    TestWebsocketMessage response;
    response.set_data(std::vector<unsigned char>(error_message.begin(), error_message.end()));
    response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
    client.connect().get();

    // Arrange - Expectations
    client.set_on_error_handler([this](const std::exception& e) {
        increment_call_counter();
    });
    set_expected_call_count(1);

    // Act
    mock_server.send_message(response);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Verify
    verify_call_count(1);
}
