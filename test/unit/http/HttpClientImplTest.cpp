#include "gtest/gtest.h" // Load Google-Test first to avoid conflicts with CPP-REST-SDK

#include "HttpClientImpl.hpp"
#include "../../mocks/MockHttpServer.hpp"
#include <string>

using namespace enjin::sdk::http;

class HttpClientImplTest : public testing::Test {
public:
    HttpClientImpl class_under_test = HttpClientImpl("http://localhost/");
    enjin::test::utils::MockHttpServer mock_server;

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

        std::string base_uri = utility::conversions::to_utf8string(mock_server.uri().to_string());
        class_under_test = HttpClientImpl(base_uri);
    }

    void TearDown() override {
        class_under_test.close();
        mock_server.shutdown();
    }
};

TEST_F(HttpClientImplTest, SendRequestReceivesExpectedResponse) {
    // Arrange
    HttpResponse expected = HttpResponseBuilder()
            .code(200)
            .body("EXPECTED RESPONSE")
            .content_type(enjin::sdk::http::IHttpClient::CONTENT_TYPE)
            .build();
    HttpRequest fake_request = create_default_request();
    mock_server.map_response_for_request(fake_request, expected);

    // Act
    auto future = class_under_test.send_request(fake_request);

    future.wait();
    HttpResponse actual = future.get();

    // Assert
    ASSERT_EQ(expected, actual);
}
