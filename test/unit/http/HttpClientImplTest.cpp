#include "gtest/gtest.h" // Load Google-Test first to avoid conflicts with CPP-REST-SDK

#include "HttpClientImpl.hpp"
#include "../../utils/MockHttpServer.hpp"
#include <string>

using namespace enjin::sdk::http;

class HttpClientImplTest : public testing::Test {
public:
    HttpClientImpl class_under_test = HttpClientImpl("http://localhost/");
    enjin::test::utils::MockHttpServer mock_server;

protected:
    void SetUp() override {
        mock_server.start();

        std::string base_uri = utility::conversions::to_utf8string(mock_server.uri("/").to_string());
        class_under_test = HttpClientImpl(base_uri);
    }

    void TearDown() override {
        mock_server.shutdown();
    }
};

TEST_F(HttpClientImplTest, SendRequestReceivesResponseWithExpectedData) {
    // Arrange
    const uint16_t expected_code = 200;
    const std::string expected_body = "{}";
    web::http::http_response mock_response = web::http::http_response();
    mock_response.set_status_code(expected_code);
    mock_response.set_body(expected_body);
    mock_server.enqueue(mock_response);

    // Act
    auto future = class_under_test.send_request();

    future.wait();
    HttpResponse response = future.get();

    // Assert
    ASSERT_TRUE(response.get_code().has_value());
    ASSERT_TRUE(response.get_body().has_value());
    EXPECT_EQ(expected_code, response.get_code().value());
    EXPECT_EQ(expected_body, response.get_body().value());
}
