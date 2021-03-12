#include "gtest/gtest.h"
#include "WebsocketClientImpl.hpp"
#include "MockWebsocketServer.hpp"
#include "VerificationTestSuite.hpp"
#include <chrono>
#include <string>
#include <thread>

using namespace enjin::sdk::websockets;
using namespace enjin::test::utils;

class WebsocketClientImplTest : public VerificationTestSuite {
public:
    static constexpr char URI[] = "ws://127.0.0.1:8080/ws";

    WebsocketClientImpl class_under_test;
    MockWebsocketServer mock_server;

protected:
    void SetUp() override {
        mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
                   .ignore_message_type(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE)
                   .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
                   .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
        class_under_test.connect(URI);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    void TearDown() override {
        mock_server.close(1000, "Teardown");
    }
};

class WebsocketClientImplConnectCloseTest : public WebsocketClientImplTest {
protected:
    void SetUp() final {
        // Do nothing
    }
};

TEST_F(WebsocketClientImplConnectCloseTest, ConnectClientOpensConnectionWithServer) {
    // Arrange - Expectations
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_OPEN_TYPE, message.get_type());
    });
    set_expected_call_count(1);

    // Act
    class_under_test.connect(URI);

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplConnectCloseTest, CloseClientClosesOpenConnectionWithServer) {
    // Arrange - Data
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    class_under_test.connect(URI);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE, message.get_type());
    });
    set_expected_call_count(1);

    // Act
    class_under_test.close();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, ServerClosesConnectionClientReceivesExpected) {
    // Arrange - Data
    const int status_code = 1000;
    const std::string reason;

    // Arrange - Expectations
    class_under_test.set_close_handler([this](int actual_status, const std::string& actual_message) {
        increment_call_counter();
    });
    set_expected_call_count(1);

    // Act
    mock_server.close(status_code, reason);

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, CloseNoArgsReceiveExpectedData) {
    // Arrange - Data
    const int expected_status = 1000;

    // Arrange - Expectations
    class_under_test.set_close_handler([this, expected_status](int actual_status, const std::string& reason) {
        increment_call_counter();
        EXPECT_EQ(expected_status, actual_status);
    });
    set_expected_call_count(1);

    // Act
    class_under_test.close();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, CloseWithArgsReceiveExpectedData) {
    // Arrange - Data
    const int expected_status = 1000;
    const std::string expected_message("Client disconnecting");
    TestWebsocketMessage message;
    message.set_type(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE);

    // Arrange - Expectations
    class_under_test.set_close_handler([this, expected_status, expected_message](int actual_status,
                                                                                 const std::string& actual_message) {
        increment_call_counter();
        EXPECT_EQ(expected_status, actual_status);
        EXPECT_EQ(expected_message, actual_message);
    });
    set_expected_call_count(1);

    // Act
    class_under_test.close(expected_status, expected_message);

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, SendServerReceivesMessage) {
    // Arrange - Data
    const std::string expected("message");

    // Arrange - Expectations
    mock_server.next_message([this, expected](const TestWebsocketMessage& message) {
        increment_call_counter();

        auto data = message.get_data();
        std::string actual(data.begin(), data.end());

        EXPECT_EQ(expected, actual);
    });
    set_expected_call_count(1);

    // Act
    class_under_test.send(expected);

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, SetMessageHandlerHandlerReceivesExpectedDataFromServer) {
    // Arrange - Data
    const std::string expected("message");
    TestWebsocketMessage message;
    message.set_data(std::vector<unsigned char>(expected.begin(), expected.end()));
    message.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);

    // Arrange - Expectations
    class_under_test.set_message_handler([this, expected](const std::string& actual) {
        increment_call_counter();
        EXPECT_EQ(expected, actual);
    });
    set_expected_call_count(1);

    // Act
    mock_server.send_message(message);

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplConnectCloseTest, SetOpenHandlerHandlerReceivesExpectedDataFromServer) {
    // Arrange - Expectations
    class_under_test.set_open_handler([this]() {
        increment_call_counter();
    });
    set_expected_call_count(1);

    // Act
    class_under_test.connect(URI);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplConnectCloseTest, SetCloseHandlerHandlerReceivesExpectedDataFromServer) {
    // Arrange - Data
    const int expected_code = 1000;
    const std::string expected_reason("expected");
    class_under_test.connect(URI);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Arrange - Expectations
    class_under_test.set_close_handler([this, expected_code, expected_reason](int actual_code,
                                                                              const std::string& actual_reason) {
        increment_call_counter();
        EXPECT_EQ(expected_code, actual_code);
        EXPECT_EQ(expected_reason, actual_reason);
    });
    set_expected_call_count(1);

    // Act
    mock_server.close(expected_code, expected_reason);

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)

    class_under_test.set_close_handler([](int, const std::string&) {}); // Remove handler as part of tear down.
}
