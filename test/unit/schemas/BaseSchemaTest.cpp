#include "gtest/gtest.h" // Load Google-Test first to avoid conflicts with CPP-REST-SDK
#include "HttpClientImpl.hpp"
#include "enjinsdk/BaseSchema.hpp"
#include "../../mocks/MockHttpServer.hpp"
#include "../../utils/DummyObject.hpp"
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

using namespace enjin::sdk;
using namespace enjin::test::utils;

class BaseSchemaTest : public testing::Test {
public:
    class TestableBaseSchema : public BaseSchema {
    public:
        explicit TestableBaseSchema(TrustedPlatformMiddleware middleware)
                : BaseSchema(std::move(middleware), "test") {
        }

        const TrustedPlatformMiddleware& get_middleware() {
            return middleware;
        }

        ~TestableBaseSchema() = default;

        std::string create_request_body(graphql::AbstractGraphqlRequest& request) {
            return BaseSchema::create_request_body(request);
        }

        template<class T>
        std::future<graphql::GraphqlResponse<T>> send_request_for_one(graphql::AbstractGraphqlRequest& request) {
            return BaseSchema::send_request_for_one<T>(request);
        }

        template<class T>
        std::future<graphql::GraphqlResponse<std::vector<T>>>
        send_request_for_many(graphql::AbstractGraphqlRequest& request) {
            return BaseSchema::send_request_for_many<T>(request);
        }
    };

    class MockRequest : public graphql::AbstractGraphqlRequest {
    public:
        explicit MockRequest(std::string serialize_string = "")
                : graphql::AbstractGraphqlRequest(), serialize_string(std::move(serialize_string)) {
        };

        ~MockRequest() override = default;

        std::string serialize() override {
            return serialize_string;
        }

    private:
        std::string serialize_string;
    };

    std::unique_ptr<TestableBaseSchema> class_under_test;
    MockHttpServer mock_server;

protected:
    void SetUp() override {
        mock_server.start();

        std::string base_uri = utility::conversions::to_utf8string(mock_server.uri().to_string());
        std::unique_ptr<http::IHttpClient> http_client = std::make_unique<http::HttpClientImpl>(base_uri);
        TrustedPlatformMiddleware middleware(std::move(http_client), false);
        class_under_test = std::make_unique<TestableBaseSchema>(std::move(middleware));
    }

    void TearDown() override {
        mock_server.shutdown();
    }
};

TEST_F(BaseSchemaTest, SendRequestForOne) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    //TestableBaseSchema class_under_test = create_testable_base_schema();
    MockRequest fake_request(expected.serialize());
    std::string req_body = class_under_test->create_request_body(fake_request);
    std::stringstream res_body;
    res_body << R"({"data":{"result":)"
             << expected.serialize()
             << R"(}})";
    std::string content_type = http::IHttpClient::CONTENT_TYPE;
    http::HttpRequest http_req = http::HttpRequestBuilder().method("POST")
                                                           .path_query_fragment("/graphql/test")
                                                           .content_type(content_type)
                                                           .body(req_body)
                                                           .build();
    http::HttpResponse http_res = http::HttpResponseBuilder().code(200)
                                                             .content_type(content_type)
                                                             .body(res_body.str())
                                                             .build();
    mock_server.map_response_for_request(http_req, http_res);

    // Act
    auto response = class_under_test->send_request_for_one<DummyObject>(fake_request).get();

    // Assert
    ASSERT_EQ(expected, response.get_result().value());
}

TEST_F(BaseSchemaTest, SendRequestForMany) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    //TestableBaseSchema class_under_test = create_testable_base_schema();
    MockRequest fake_request(expected.serialize());
    std::string req_body = class_under_test->create_request_body(fake_request);
    std::stringstream res_body;
    res_body << R"({"data":{"result":[)"
             << expected.serialize()
             << R"(,)"
             << expected.serialize()
             << R"(]}})";
    std::string content_type = http::IHttpClient::CONTENT_TYPE;
    http::HttpRequest http_req = http::HttpRequestBuilder().method("POST")
                                                           .path_query_fragment("/graphql/test")
                                                           .content_type(content_type)
                                                           .body(req_body)
                                                           .build();
    http::HttpResponse http_res = http::HttpResponseBuilder().code(200)
                                                             .content_type(content_type)
                                                             .body(res_body.str())
                                                             .build();
    mock_server.map_response_for_request(http_req, http_res);

    // Act
    auto response = class_under_test->send_request_for_many<DummyObject>(fake_request).get();

    // Assert
    for (const auto& actual : response.get_result().value()) {
        EXPECT_EQ(expected, actual);
    }
}
