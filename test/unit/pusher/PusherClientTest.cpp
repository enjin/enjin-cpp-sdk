#include "gtest/gtest.h"
#include "enjinsdk/internal/pusher/Constants.hpp"
#include "enjinsdk/internal/pusher/PusherClient.hpp"
#include "../../mocks/MockSubscriptionEventListener.hpp"
#include "../../mocks/MockWebSocketClientImpl.hpp"
#include "../../mocks/MockWebsocketServer.hpp"
#include "../../suites/VerificationTestSuite.hpp"
#include <chrono>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

using namespace enjin::pusher;
using namespace enjin::sdk;
using namespace enjin::test::utils;

class PusherClientTest : public VerificationTestSuite {
public:
    static constexpr char DEFAULT_CHANNEL_NAME[] = "test.channel";
    static constexpr char DEFAULT_CLUSTER[] = "mt1";
    static constexpr char DEFAULT_EVENT_NAME[] = "TestEvent";
    static constexpr char DEFAULT_KEY[] = "xyz";

    std::shared_ptr<MockWebSocketClientImpl> mock_ws_client = std::make_shared<MockWebSocketClientImpl>();
    std::shared_ptr<MockSubscriptionEventListener> mock_listener = std::make_shared<MockSubscriptionEventListener>();
    MockWebsocketServer mock_server;

    [[nodiscard]] PusherClient create_testable_pusher_client() const {
        PusherOptions options = create_default_pusher_options();
        return PusherClient(mock_ws_client, DEFAULT_KEY, options);
    }

    static std::string create_default_event(const std::string& channel = "",
                                            const std::string& data = "null") {
        return (std::stringstream()
                << R"({"event":")"
                << DEFAULT_EVENT_NAME
                << R"(","channel":")"
                << channel
                << R"(","data":)"
                << data
                << R"(})"
        ).str();
    }

    static PusherOptions create_default_pusher_options() {
        PusherOptions options;
        options.set_cluster(DEFAULT_CLUSTER);
        options.set_encrypted(true);
        return options;
    }

    static std::string create_subscription_success_message(const std::string& channel = "",
                                                           const std::string& data = "null") {
        return (std::stringstream()
                << R"({"event":")"
                << enjin::pusher::Constants::CHANNEL_SUBSCRIPTION_SUCCEEDED
                << R"(","channel":")"
                << channel
                << R"(","data":)"
                << data
                << R"(})"
        ).str();
    }

    static std::string create_subscription_error_message() {
        return (std::stringstream()
                << R"({"event":")"
                << enjin::pusher::Constants::CHANNEL_SUBSCRIPTION_ERROR
                << R"("})"
        ).str();
    }
};

TEST_F(PusherClientTest, Connect) {
    // Arrange
    PusherClient client = create_testable_pusher_client();

    // Assert
    EXPECT_NO_THROW(client.connect([](ConnectionState state) {}, [](const std::exception& e) {}).wait());
    EXPECT_EQ(ConnectionState::CONNECTED, client.get_state());

    client.disconnect().wait();
}

TEST_F(PusherClientTest, Disconnect) {
    // Arrange
    PusherClient client = create_testable_pusher_client();
    client.connect([](ConnectionState state) {}, [](const std::exception& e) {}).wait();

    // Assert
    EXPECT_NO_THROW(client.disconnect().wait());
    EXPECT_EQ(ConnectionState::DISCONNECTED, client.get_state());
}

TEST_F(PusherClientTest, SubscribeClientSendsMessageToServerAndSubscribesToChannelAfterReceivingSuccessResponse) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.connect([](ConnectionState state) {}, [](const std::exception& e) {}).wait();

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
    client.subscribe(channel_name).wait();

    // Verify
    verify_call_count(2);

    // Assert
    EXPECT_TRUE(client.is_subscribed(channel_name));

    client.disconnect().wait();
}

TEST_F(PusherClientTest, SubscribeClientSendsMessageToServerAndRaisesErrorAfterReceivingErrorResponse) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.connect([](ConnectionState state) {},
                   [this](const std::exception& e) {
                       increment_call_counter();
                   }).wait();

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
    client.subscribe(channel_name).wait();

    // Verify
    verify_call_count(2);

    client.disconnect().wait();
}

TEST_F(PusherClientTest, UnsubscribeClientSendsMessageToServerAndUnsubscribesFromChannel) {
    // Arrange - Data
    const std::string channel_name(DEFAULT_CHANNEL_NAME);
    PusherClient client = create_testable_pusher_client();
    client.connect([](ConnectionState state) {}, [](const std::exception& e) {}).wait();
    mock_server.next_message([this, channel_name](const TestWebsocketMessage& message) {
        const std::string success_message = create_subscription_success_message(channel_name);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(success_message.begin(), success_message.end()));
        response.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        mock_server.send_message(response);
    });
    client.subscribe(channel_name).wait();

    // Arrange - Expectations
    EXPECT_TRUE(client.is_subscribed_or_pending(channel_name));
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
    });
    set_expected_call_count(1);

    // Act
    client.unsubscribe(channel_name);

    // Verify
    verify_call_count(2);

    // Assert
    EXPECT_FALSE(client.is_subscribed_or_pending(channel_name));

    client.disconnect().wait();
}

TEST_F(PusherClientTest, ListenerIsCalledWhenBoundEventIsReceived) {
    // Arrange - Data
    const std::string event_name(DEFAULT_EVENT_NAME);
    const std::string event_message = create_default_event();
    TestWebsocketMessage message;
    PusherClient client = create_testable_pusher_client();
    message.set_data(std::vector<unsigned char>(event_message.begin(), event_message.end()));
    message.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
    client.connect([](ConnectionState state) {}, [](const std::exception& e) {}).wait();
    client.bind(event_name, mock_listener);

    // Arrange - Expectations
    EXPECT_CALL(*mock_listener, on_event(testing::An<const PusherEvent&>()))
            .Times(1);

    // Act
    mock_server.send_message(message);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Assert (see: Arrange - Expectations)

    client.disconnect().wait();
}

TEST_F(PusherClientTest, ListenerIsNotCalledWhenUnboundEventIsReceived) {
    // Arrange - Data
    const std::string event_name(DEFAULT_EVENT_NAME);
    const std::string event_message = create_default_event();
    TestWebsocketMessage message;
    PusherClient client = create_testable_pusher_client();
    message.set_data(std::vector<unsigned char>(event_message.begin(), event_message.end()));
    message.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
    client.connect([](ConnectionState state) {}, [](const std::exception& e) {}).wait();
    client.bind(event_name, mock_listener);
    client.unbind(event_name);

    // Arrange - Expectations
    EXPECT_CALL(*mock_listener, on_event(testing::An<const PusherEvent&>()))
            .Times(0);

    // Act
    mock_server.send_message(message);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Assert (see: Arrange - Expectations)

    client.disconnect().wait();
}
