#include "gtest/gtest.h"
#include "WebsocketClientImpl.hpp"
#include "../../utils/MockWebsocketServer.hpp"
#include <atomic>
#include <chrono>
#include <mutex>
#include <string>

using namespace enjin::sdk::websockets;
using namespace enjin::test::utils;

class WebsocketClientImplTest : public testing::Test {
public:
    static constexpr char URI[] = "ws://localhost:9980/ws";

    WebsocketClientImpl class_under_test;
    MockWebsocketServer mock_server;

    /* Members for setting expectations and verifying calls to functional arguments.
     */
    std::atomic_int call_counter = 0;
    int expected_count = 0;

    void set_expected_call_count(int count) {
        expected_count = count;
    }

    void increment_call_counter() {
        call_counter++;
    }

    void verify_call_count(int time = 0) const {
        // Waits and gives the calls an opportunity to be made if asynchronous
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        std::condition_variable condition_variable;
        condition_variable.wait_for(lock, std::chrono::seconds(time), [this]() {
            return expected_count == call_counter;
        });

        EXPECT_EQ(expected_count, call_counter);
    }

protected:
    void SetUp() override {
        class_under_test.connect(URI).wait();
    }

    void TearDown() override {
        class_under_test.close().wait();
    }
};

class WebsocketClientImplConnectCloseTest : public WebsocketClientImplTest {
protected:
    void SetUp() final {
        // Do nothing
    }

    void TearDown() final {
        // Do nothing
    }
};

TEST_F(WebsocketClientImplConnectCloseTest, CloseClientCosesConnectionWithServerNoException) {
    // Assert
    EXPECT_NO_THROW(class_under_test.connect(URI).wait());
    EXPECT_NO_THROW(class_under_test.close().wait());
}

TEST_F(WebsocketClientImplTest, ServerClosesConnectionClientReceivesExpected) {
    // Arrange - Data
    const int expected_status = (int) web::websockets::client::websocket_close_status::normal;
    const std::string expected_message("Normal");
    const int expected_error_value = 0;
    TestWebsocketMessage message;
    message.set_type(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE);

    // Arrange - Expectations
    class_under_test.set_close_handler([expected_status, expected_message, expected_error_value]
                                               (int actual_status,
                                                const std::string& actual_message,
                                                const std::error_code& actual_error) {
        EXPECT_EQ(expected_status, actual_status);
        EXPECT_EQ(expected_message, actual_message);
        EXPECT_EQ(expected_error_value, actual_error.value());
    });

    // Act
    mock_server.send_message(message);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, CloseNoArgsReceiveExpectedData) {
    // Arrange - Data
    const int expected_status = (int) web::websockets::client::websocket_close_status::normal;
    const std::string expected_message("Normal");
    const int expected_error_value = 0;
    TestWebsocketMessage message;
    message.set_type(enjin::test::utils::WebsocketMessageType::WEBSOCKET_CLOSE_TYPE);

    // Arrange - Expectations
    class_under_test.set_close_handler([this, expected_status, expected_message, expected_error_value]
                                               (int actual_status,
                                                const std::string& actual_message,
                                                const std::error_code& actual_error) {
        increment_call_counter();
        EXPECT_EQ(expected_status, actual_status);
        EXPECT_EQ(expected_message, actual_message);
        EXPECT_EQ(expected_error_value, actual_error.value());
    });
    set_expected_call_count(1);

    // Act
    class_under_test.close().wait();

    // Verify
    verify_call_count(2);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, CloseWithArgsReceiveExpectedData) {
    // Arrange - Data
    const int expected_status = (int) web::websockets::client::websocket_close_status::normal;
    const std::string expected_message("Client disconnecting");
    const int expected_error_value = 0;
    TestWebsocketMessage message;
    message.set_type(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE);

    // Arrange - Expectations
    class_under_test.set_close_handler([this, expected_status, expected_message, expected_error_value]
                                               (int actual_status,
                                                const std::string& actual_message,
                                                const std::error_code& actual_error) {
        increment_call_counter();
        EXPECT_EQ(expected_status, actual_status);
        EXPECT_EQ(expected_message, actual_message);
        EXPECT_EQ(expected_error_value, actual_error.value());
    });
    set_expected_call_count(1);

    // Act
    class_under_test.close(expected_status, expected_message).wait();

    // Verify
    verify_call_count(2);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, SendServerReceivesMessage) {
    // Arrange - Data
    const std::string expected("message");

    // Arrange - Expectations
    mock_server.next_message([expected](const TestWebsocketMessage& message) {
        auto data = message.get_data();
        std::string actual(data.begin(), data.end());

        EXPECT_EQ(expected, actual);
    });

    // Act
    class_under_test.send(expected).wait();

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
    verify_call_count(2);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, SetPingHandlerHandlerReceivesExpectedDataFromServer) {
    // Arrange - Data
    const std::string expected("message");
    TestWebsocketMessage message;
    message.set_data(std::vector<unsigned char>(expected.begin(), expected.end()));
    message.set_type(WebsocketMessageType::WEBSOCKET_PING_TYPE);

    // Arrange - Expectations
    class_under_test.set_ping_handler([this, expected](const std::string& actual) {
        increment_call_counter();
        EXPECT_EQ(expected, actual);
    });
    set_expected_call_count(1);

    // Act
    mock_server.send_message(message);

    // Verify
    verify_call_count(2);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, SetPongHandlerHandlerReceivesExpectedDataFromServer) {
    // Arrange - Data
    const std::string expected("message");
    TestWebsocketMessage message;
    message.set_data(std::vector<unsigned char>(expected.begin(), expected.end()));
    message.set_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);

    // Arrange - Expectations
    class_under_test.set_pong_handler([this, expected](const std::string& actual) {
        increment_call_counter();
        EXPECT_EQ(expected, actual);
    });
    set_expected_call_count(1);

    // Act
    mock_server.send_message(message);

    // Verify
    verify_call_count(2);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, ServerPingsClientExpectClientPongsServer) {
    // Arrange - Data
    const WebsocketMessageType expected = WebsocketMessageType::WEBSOCKET_PONG_TYPE;
    TestWebsocketMessage message;
    message.set_type(WebsocketMessageType::WEBSOCKET_PING_TYPE);

    // Arrange - Expectations
    mock_server.next_message([this, expected](const TestWebsocketMessage& message) {
        increment_call_counter();
        WebsocketMessageType actual = message.get_type();
        EXPECT_EQ(expected, actual);
    });
    set_expected_call_count(1);

    // Act
    mock_server.send_message(message);

    // Verify
    verify_call_count(2);

    // Assert (see: Arrange - Expectations)
}
