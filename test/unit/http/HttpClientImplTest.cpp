#include "gtest/gtest.h" // Load Google-Test first to avoid conflicts with CPP-REST-SDK
#include "HttpClientImpl.hpp"
#include "MockHttpServer.hpp"
#include "VerificationTestSuite.hpp"
#include <memory>
#include <string>

using namespace enjin::sdk::http;
using namespace enjin::test::utils;

class HttpClientImplTest : public VerificationTestSuite {
public:
    HttpClientImpl class_under_test = HttpClientImpl("http://localhost/");
    MockHttpServer mock_server;
    std::string base_uri;

    static HttpRequest create_default_request() {
        return HttpRequestBuilder()
                .method(utility::conversions::to_utf8string(web::http::methods::POST))
                .path_query_fragment("/")
                .body("{}")
                .content_type(enjin::sdk::http::IHttpClient::CONTENT_TYPE)
                .build();
    }

protected:
    void SetUp() override {
        mock_server.start();

        base_uri = utility::conversions::to_utf8string(mock_server.uri().to_string());
        class_under_test = HttpClientImpl(base_uri);
    }

    void TearDown() override {
        class_under_test.close();
        mock_server.shutdown();
    }
};

TEST_F(HttpClientImplTest, SendRequestReceivesExpectedResponse) {
    // Arrange
    HttpClientImpl client = HttpClientImpl(base_uri);
    HttpResponse expected = HttpResponseBuilder()
            .code(200)
            .body("EXPECTED RESPONSE")
            .content_type(enjin::sdk::http::IHttpClient::CONTENT_TYPE)
            .build();
    HttpRequest dummy_request = create_default_request();
    mock_server.map_response_for_request(dummy_request, expected);

    // Act
    HttpResponse actual = client.send_request(dummy_request).get();

    // Assert
    ASSERT_EQ(expected, actual);

    client.close();
}

TEST_F(HttpClientImplTest, SetsAuthorizationHeaderWhenTrustedPlatformHandlerIsAuthenticated) {
    // Arrange - Data
    auto expected_header_name = utility::conversions::to_string_t(TrustedPlatformHandler::AUTHORIZATION);
    auto expected_header_value = U("Bearer xyz");
    HttpClientImpl client = HttpClientImpl(base_uri);
    HttpRequest fake_request = create_default_request();
    std::shared_ptr<TrustedPlatformHandler> fake_handler = std::make_shared<TrustedPlatformHandler>();
    fake_handler->set_auth_token("xyz");
    client.set_trusted_platform_handler(fake_handler);

    // Arrange - Expectations
    mock_server.next_request([this, expected_header_name, expected_header_value]
    (const web::http::http_request& request) {
        increment_call_counter();

        EXPECT_TRUE(request.headers().has(expected_header_name));

        auto iter = request.headers().find(expected_header_name);
        if (iter == request.headers().end()) {
            return;
        }

        auto actual_header_value = iter->second;
        EXPECT_EQ(expected_header_value, actual_header_value);
    });
    set_expected_call_count(1);

    // Act
    client.send_request(fake_request).get();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)

    client.close();
}

TEST_F(HttpClientImplTest, DoesNotSetAuthorizationHeaderWhenTrustedPlatformHandlerIsNotAuthenticated) {
    // Arrange - Data
    auto expected_header_name = utility::conversions::to_string_t(TrustedPlatformHandler::AUTHORIZATION);
    HttpClientImpl client = HttpClientImpl(base_uri);
    HttpRequest fake_request = create_default_request();
    std::shared_ptr<TrustedPlatformHandler> fake_handler = std::make_shared<TrustedPlatformHandler>();
    client.set_trusted_platform_handler(fake_handler);

    // Arrange - Expectations
    mock_server.next_request([this, expected_header_name](const web::http::http_request& request) {
        increment_call_counter();

        EXPECT_FALSE(request.headers().has(expected_header_name));
    });
    set_expected_call_count(1);

    // Act
    client.send_request(fake_request).get();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)

    client.close();
}

TEST_F(HttpClientImplTest, SetsUserAgentHeaderWithExpectedPrefix) {
    // Arrange - Data
    auto expected_prefix = utility::conversions::to_string_t(TrustedPlatformHandler::USER_AGENT_PREFIX);
    HttpClientImpl client = HttpClientImpl(base_uri);
    HttpRequest fake_request = create_default_request();
    std::shared_ptr<TrustedPlatformHandler> fake_handler = std::make_shared<TrustedPlatformHandler>();
    client.set_trusted_platform_handler(fake_handler);

    // Arrange - Expectations
    mock_server.next_request([this, expected_prefix](const web::http::http_request& request) {
        increment_call_counter();

        bool has_user_agent_header = request.headers().has(web::http::header_names::user_agent);

        EXPECT_TRUE(has_user_agent_header);

        if (has_user_agent_header) {
            auto header_value = request.headers().find(web::http::header_names::user_agent)->second;
            EXPECT_TRUE(header_value.find(expected_prefix) == 0);
        }
    });
    set_expected_call_count(1);

    // Act
    client.send_request(fake_request).get();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)

    client.close();
}
