#include "gtest/gtest.h"
#include "WebsocketClientImpl.hpp"
#include "../../utils/MockWebsocketServer.hpp"
#include <string>

using namespace enjin::sdk::websockets;
using namespace enjin::test::utils;

class WebsocketClientImplTest : public testing::Test {
public:
    static constexpr char URI[] = "ws://localhost:9980/ws";

    WebsocketClientImpl class_under_test;
    MockWebsocketServer mock_server;

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
    ASSERT_NO_THROW(class_under_test.connect(URI).wait());
    ASSERT_NO_THROW(class_under_test.close().wait());
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

TEST_F(WebsocketClientImplTest, CloseNoArgsReceiveExpected) {
    // Arrange - Data
    const int expected_status = (int) web::websockets::client::websocket_close_status::normal;
    const std::string expected_message("Normal");
    const int expected_error_value = 0;
    TestWebsocketMessage message;
    message.set_type(enjin::test::utils::WebsocketMessageType::WEBSOCKET_CLOSE_TYPE);

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
    class_under_test.close().wait();

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, CloseWithArgsReceiveExpected) {
    // Arrange - Data
    const int expected_status = (int) web::websockets::client::websocket_close_status::normal;
    const std::string expected_message("Client disconnecting");
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
    class_under_test.close(expected_status, expected_message).wait();

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, SendServerReceivesMessage) {
    // Arrange - Data
    const std::string expected("message");

    // Arrange - Expectations
    mock_server.next_message([expected](const TestWebsocketMessage& message) {
        auto data = message.get_data();
        std::string actual(data.begin(), data.end());

        ASSERT_EQ(expected, actual);
    });

    // Act
    class_under_test.send(expected).wait();

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, ServerSendsMessageClientReceivesExpected) {
    // Arrange - Data
    const std::string expected("message");
    TestWebsocketMessage message;
    message.set_data(std::vector<unsigned char>(expected.begin(), expected.end()));
    message.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);

    // Arrange - Expectations
    class_under_test.set_message_handler([expected](const std::string& actual) {
        ASSERT_EQ(expected, actual);
    });

    // Act
    mock_server.send_message(message);

    // Assert (see: Arrange - Expectations)
}

TEST_F(WebsocketClientImplTest, ServerPingsClientExpectClientPongsServer) {
    // Arrange - Data
    const WebsocketMessageType expected = WebsocketMessageType::WEBSOCKET_PONG_TYPE;
    TestWebsocketMessage message;
    message.set_type(WebsocketMessageType::WEBSOCKET_PING_TYPE);

    // Arrange - Expectations
    mock_server.next_message([expected](const TestWebsocketMessage& message) {
        WebsocketMessageType actual = message.get_type();
        ASSERT_EQ(expected, actual);
    });

    // Act
    mock_server.send_message(message);

    // Assert (see: Arrange - Expectations)
}
