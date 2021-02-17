#include "gtest/gtest.h"
#include "enjinsdk/internal/pusher/PusherClient.hpp"
#include "../../suites/PusherClientTestSuite.hpp"
#include "../../suites/VerificationTestSuite.hpp"
#include <chrono>
#include <string>
#include <thread>

using namespace enjin::pusher;
using namespace enjin::test::utils;

class PusherClientReconnectTest : public PusherClientTestSuite,
                                  public VerificationTestSuite {
protected:
    void SetUp() override {
        mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE)
                   .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
                   .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    }
};

TEST_F(PusherClientReconnectTest, ReceivesGenericClosingCodeDoesReconnectToServer) {
    // Arrange - Data
    const int status_code = 1000;
    const std::string reason;
    PusherClient client = create_testable_pusher_client();
    mock_server.next_message([](const TestWebsocketMessage& message) { /* Consume initial open message */ });
    client.connect();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_OPEN_TYPE, message.get_type());
    });
    set_expected_call_count(1);

    // Act
    mock_server.close(status_code, reason);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Verify
    verify_call_count(2);

    // Assert
    EXPECT_EQ(ConnectionState::CONNECTED, client.get_state());

    client.disconnect();
}

TEST_F(PusherClientReconnectTest, ReceivesPusherClosingCodeDoesNotReconnectToServer) {
    // Arrange - Data
    const int status_code = 4000;
    const std::string reason;
    PusherClient client = create_testable_pusher_client();
    mock_server.next_message([](const TestWebsocketMessage& message) { /* Consume initial open message */ });
    client.connect();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    mock_server.close(status_code, reason);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    EXPECT_EQ(ConnectionState::DISCONNECTED, client.get_state());

    client.disconnect();
}
