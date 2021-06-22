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
#include "WebsocketClientImpl.hpp"
#include "MockWebsocketServer.hpp"
#include "VerificationTestSuite.hpp"
#include <string>

using namespace enjin::sdk::websockets;
using namespace enjin::test::mocks;
using namespace enjin::test::suites;

class WebsocketClientImplTest : public VerificationTestSuite,
                                public testing::Test {
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
        class_under_test.connect(URI).get();
    }

    void TearDown() override {
        class_under_test.close().get();
    }
};

class WebsocketClientImplConnectCloseTest : public WebsocketClientImplTest {
protected:
    void SetUp() final {
        // Do nothing
    }
};

TEST_F(WebsocketClientImplConnectCloseTest, ConnectClientOpensConnectionWithServer) {
    // Arrange - Data
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);

    // Arrange - Expectations
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_OPEN_TYPE, message.get_type());
    });
    set_expected_call_count(1);

    // Act
    class_under_test.connect(URI).get();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplConnectCloseTest, ClientReconnectsAfterConnectionIsClosed) {
    // Arrange - Data
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    class_under_test.set_allow_reconnecting(true);
    class_under_test.set_allowed_reconnect_attempts(5);
    class_under_test.connect(URI).get();
    mock_server.next_message([](const TestWebsocketMessage& message) { /* Consume initial open message */ });

    // Arrange - Expectations
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_OPEN_TYPE, message.get_type());
    });
    set_expected_call_count(1);

    // Act
    mock_server.close();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplConnectCloseTest, ConnectConnectingResultsInErrorWhenFailed) {
    // Arrange
    mock_server.stop();

    // Act
    std::future<void> future = class_under_test.connect(URI);

    // Assert
    ASSERT_ANY_THROW(future.get());
}

TEST_F(WebsocketClientImplConnectCloseTest, ConnectCloseMessageHandlerReceivesMessage) {
    // Arrange - Data
    mock_server.close();

    // Arrange - Expectations
    class_under_test.set_close_handler([this](int status, const std::string& reason) {
        increment_call_counter();
    });
    set_expected_call_count(1);

    // Act
    std::future<void> future = class_under_test.connect(URI);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplConnectCloseTest, CloseClientClosesOpenConnectionWithServer) {
    // Arrange - Data
    mock_server.ignore_message_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PING_TYPE)
               .ignore_message_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);
    class_under_test.connect(URI).get();

    // Arrange - Expectations
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE, message.get_type());
    });
    set_expected_call_count(1);

    // Act
    class_under_test.close().get();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, ServerClosesConnectionClientReceivesExpected) {
    // Arrange - Data
    const int expected_status = 1000;
    const std::string expected_reason("Test closure");

    // Arrange - Expectations
    class_under_test.set_close_handler([this, expected_status, expected_reason](int actual_status,
                                                                                const std::string& actual_reason) {
        increment_call_counter();
        EXPECT_EQ(expected_status, actual_status);
        EXPECT_EQ(expected_reason, actual_reason);
    });
    set_expected_call_count(1);

    // Act
    mock_server.close(expected_status, expected_reason);

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
    class_under_test.close().get();

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
    class_under_test.close(expected_status, expected_message).get();

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
    class_under_test.connect(URI).get();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplConnectCloseTest, SetCloseHandlerHandlerReceivesExpectedDataFromServer) {
    // Arrange - Data
    const int expected_code = 1000;
    const std::string expected_reason("expected");
    class_under_test.connect(URI).get();

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
