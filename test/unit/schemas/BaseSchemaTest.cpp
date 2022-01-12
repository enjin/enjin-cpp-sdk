/* Copyright 2021 Enjin Pte. Ltd.
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
#include "FakeGraphqlRequest.hpp"
#include "MockHttpClient.hpp"
#include "TestableBaseSchema.hpp"
#include "enjinsdk/HttpHeaders.hpp"
#include <string>

using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using namespace enjin::test::utils;

class BaseSchemaTest : public testing::Test {
public:
    [[nodiscard]] static TestableBaseSchema create_testable_base_schema() {
        return TestableBaseSchema(TrustedPlatformMiddleware(std::make_unique<MockHttpClient>()));
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
    ASSERT_FALSE(request.has_header(AUTHORIZATION));
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
    ASSERT_TRUE(request.has_header(AUTHORIZATION));
}
