#include "HttpClientImpl.hpp"
#include "MockHttpServer.hpp"
#include "VerificationTestSuite.hpp"
#include "gtest/gtest.h"

using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using namespace enjin::test::suites;

class HttpClientImplTest : public VerificationTestSuite,
                           public testing::Test {
public:
    static constexpr char JSON[] = "application/json; charset=utf-8";

    MockHttpServer mock_server;

    HttpClientImpl create_client() {
        return HttpClientImpl(mock_server.uri());
    }

    static HttpRequest create_default_request() {
        return HttpRequestBuilder()
                .method("POST")
                .path_query_fragment("/")
                .body("{}")
                .content_type(JSON)
                .build();
    }

protected:
    void SetUp() override {
        mock_server.start();
    }

    void TearDown() override {
        mock_server.stop();
    }
};

TEST_F(HttpClientImplTest, SendRequestReceivesExpectedResponse) {
    // Arrange - Data
    HttpResponse expected = HttpResponseBuilder()
            .code(200)
            .body("{}")
            .content_type(JSON)
            .build();
    HttpClientImpl client = create_client();
    HttpRequest dummy_request = create_default_request();
    client.start();

    // Arrange - Stubbing
    mock_server.given(dummy_request)
               .respond_with(expected);

    // Act
    HttpResponse actual = client.send_request(dummy_request).get();

    // Assert
    ASSERT_EQ(expected, actual);
}
