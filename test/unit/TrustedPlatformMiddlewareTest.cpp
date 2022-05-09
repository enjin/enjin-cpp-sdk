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
#include "MockHttpClient.hpp"
#include "enjinsdk/HttpHeaders.hpp"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include <memory>
#include <string>

using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using ::testing::Return;

class TrustedPlatformMiddlewareTest : public testing::Test {
public:
    std::unique_ptr<TrustedPlatformMiddleware> class_under_test;

protected:
    void SetUp() override {
        testing::Test::SetUp();

        class_under_test = std::make_unique<TrustedPlatformMiddleware>(std::make_unique<NiceMockHttpClient>());
    }
};

TEST_F(TrustedPlatformMiddlewareTest, IsAuthenticatedAuthTokenIsNotEmptyOrWhitespaceReturnsTrue) {
    // Arrange
    const std::string auth_token("xyz");
    class_under_test->set_auth_token(auth_token);

    // Act
    const bool actual = class_under_test->is_authenticated();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TrustedPlatformMiddlewareTest, IsAuthenticatedAuthTokenIsNotSetReturnsFalse) {
    // Act
    const bool actual = class_under_test->is_authenticated();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TrustedPlatformMiddlewareTest, IsAuthenticatedAuthTokenIsEmptyReturnsFalse) {
    // Arrange
    const std::string auth_token;
    class_under_test->set_auth_token(auth_token);

    // Act
    const bool actual = class_under_test->is_authenticated();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TrustedPlatformMiddlewareTest, IsAuthenticatedAuthTokenIsWhitespaceReturnsFalse) {
    // Arrange
    const std::string auth_token(" ");
    class_under_test->set_auth_token(auth_token);

    // Act
    const bool actual = class_under_test->is_authenticated();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TrustedPlatformMiddlewareTest, CreateRequestRequestDoesNotHaveAuthorizationHeaderWhenAuthTokenIsNotSet) {
    // Assumptions
    ASSERT_FALSE(class_under_test->is_authenticated()) << "Assume middleware is not authenticated.";

    // Act
    const HttpRequest req = class_under_test->create_request();

    // Assert
    ASSERT_FALSE(req.has_header(AUTHORIZATION)) << "Assert request does not have authorization header.";
}

TEST_F(TrustedPlatformMiddlewareTest, CreateRequestRequestDoesHaveAuthorizationHeaderWhenAuthTokenIsSet) {
    // Arrange
    const std::string auth_token("xyz");
    class_under_test->set_auth_token(auth_token);

    // Assumptions
    ASSERT_TRUE(class_under_test->is_authenticated()) << "Assume middleware is authenticated.";

    // Act
    const HttpRequest req = class_under_test->create_request();

    // Assert
    ASSERT_TRUE(req.has_header(AUTHORIZATION)) << "Assert request has authorization header.";
}

TEST_F(TrustedPlatformMiddlewareTest, IsClosedHttpClientIsNotOpenReturnsTrue) {
    // Arrange - Data
    auto& client = dynamic_cast<NiceMockHttpClient&>(*class_under_test->get_client());

    // Arrange - Expectations
    EXPECT_CALL(client, is_open()).WillOnce(Return(false));

    // Act
    const bool actual = class_under_test->is_closed();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TrustedPlatformMiddlewareTest, IsClosedHttpClientIsOpenReturnsFalse) {
    // Arrange - Data
    auto& client = dynamic_cast<NiceMockHttpClient&>(*class_under_test->get_client());

    // Arrange - Expectations
    EXPECT_CALL(client, is_open()).WillOnce(Return(true));

    // Act
    const bool actual = class_under_test->is_closed();

    // Assert
    ASSERT_FALSE(actual);
}
