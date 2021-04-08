#include "DummyObject.hpp"
#include "FakeGraphqlRequest.hpp"
#include "HttpClientImpl.hpp"
#include "MockHttpServer.hpp"
#include "TestableBaseSchema.hpp"
#include "gtest/gtest.h"
#include <memory>
#include <sstream>
#include <string>

using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using namespace enjin::test::utils;

class BaseSchemaHttpTest : public testing::Test {
public:
    static constexpr HttpMethod HTTP_METHOD = HttpMethod::Post;
    static constexpr char DEFAULT_PATH_QUERY_FRAGMENT[] = "/graphql/test";
    static constexpr char JSON[] = "application/json; charset=utf-8";

    MockHttpServer mock_server;

    TestableBaseSchema create_testable_base_schema() {
        auto client = std::make_unique<http::HttpClientImpl>(mock_server.uri());
        client->start();

        return TestableBaseSchema(TrustedPlatformMiddleware(std::move(client), false));
    }

protected:
    void SetUp() override {
        mock_server.start();
    }

    void TearDown() override {
        mock_server.stop();
    }
};

TEST_F(BaseSchemaHttpTest, SendRequestForOne) {
    // Arrange - Data
    DummyObject expected = DummyObject::create_default_dummy_object();
    TestableBaseSchema schema = create_testable_base_schema();
    FakeGraphqlRequest fake_request(expected.serialize());
    std::string req_body = schema.create_request_body(fake_request);
    std::stringstream res_body;
    res_body << R"({"data":{"result":)"
             << expected.serialize()
             << R"(}})";
    HttpRequest http_req = http::HttpRequestBuilder().method(HTTP_METHOD)
                                                     .path_query_fragment(DEFAULT_PATH_QUERY_FRAGMENT)
                                                     .content_type(JSON)
                                                     .body(req_body)
                                                     .build();
    HttpResponse http_res = http::HttpResponseBuilder().code(200)
                                                       .content_type(JSON)
                                                       .body(res_body.str())
                                                       .build();

    // Arrange - Stubbing
    mock_server.given(http_req)
               .respond_with(http_res);

    // Act
    auto response = schema.send_request_for_one<DummyObject>(fake_request).get();

    // Assert
    ASSERT_EQ(expected, response.get_result().value());
}

TEST_F(BaseSchemaHttpTest, SendRequestForMany) {
    // Arrange - Data
    DummyObject expected = DummyObject::create_default_dummy_object();
    TestableBaseSchema schema = create_testable_base_schema();
    FakeGraphqlRequest fake_request(expected.serialize());
    std::string req_body = schema.create_request_body(fake_request);
    std::stringstream res_body;
    res_body << R"({"data":{"result":[)"
             << expected.serialize()
             << R"(,)"
             << expected.serialize()
             << R"(]}})";
    HttpRequest http_req = http::HttpRequestBuilder().method(HTTP_METHOD)
                                                     .path_query_fragment(DEFAULT_PATH_QUERY_FRAGMENT)
                                                     .content_type(JSON)
                                                     .body(req_body)
                                                     .build();
    HttpResponse http_res = http::HttpResponseBuilder().code(200)
                                                       .content_type(JSON)
                                                       .body(res_body.str())
                                                       .build();

    // Arrange - Stubbing
    mock_server.given(http_req)
               .respond_with(http_res);

    // Act
    auto response = schema.send_request_for_many<DummyObject>(fake_request).get();

    // Assert
    for (const auto& actual : response.get_result().value()) {
        EXPECT_EQ(expected, actual);
    }
}
