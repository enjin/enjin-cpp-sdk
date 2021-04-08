#include "FakeGraphqlRequest.hpp"
#include "TestableBaseSchema.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using namespace enjin::test::utils;

class BaseSchemaTest : public testing::Test {
public:
    [[nodiscard]] static TestableBaseSchema create_testable_base_schema() {
        return TestableBaseSchema(TrustedPlatformMiddleware(nullptr, false));
    }

    [[nodiscard]] static FakeGraphqlRequest create_default_fake_request() {
        return FakeGraphqlRequest("");
    }
};

TEST_F(BaseSchemaTest, CreateRequestBody) {
    // Arrange
    const std::string expected(R"({"query":"","variables":{"var":1}})");
    TestableBaseSchema schema = create_testable_base_schema();
    FakeGraphqlRequest fake_request(R"({"var":1})");

    // Act
    std::string actual = schema.create_request_body(fake_request);

    // Asert
    ASSERT_EQ(expected, actual);
}

TEST_F(BaseSchemaTest, CreateRequestHandlerIsNotAuthenticatedRequestDoesNotHaveAuthorizationHeader) {
    // Arrange
    TestableBaseSchema schema = create_testable_base_schema();
    FakeGraphqlRequest dummy_request = create_default_fake_request();

    EXPECT_FALSE(schema.get_middleware().get_handler()->is_authenticated());

    // Act
    HttpRequest request = schema.create_request(dummy_request);

    // Asert
    ASSERT_FALSE(request.has_header(TrustedPlatformHandler::AUTHORIZATION));
}

TEST_F(BaseSchemaTest, CreateRequestHandlerIsAuthenticatedRequestHasAuthorizationHeader) {
    // Arrange
    TestableBaseSchema schema = create_testable_base_schema();
    FakeGraphqlRequest dummy_request = create_default_fake_request();
    schema.get_middleware().get_handler()->set_auth_token("xyz");

    EXPECT_TRUE(schema.get_middleware().get_handler()->is_authenticated());

    // Act
    HttpRequest request = schema.create_request(dummy_request);

    // Asert
    ASSERT_TRUE(request.has_header(TrustedPlatformHandler::AUTHORIZATION));
}
