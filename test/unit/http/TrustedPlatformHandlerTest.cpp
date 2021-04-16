/* Copyright 2021 Enjin Pte Ltd.
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

#include "enjinsdk/TrustedPlatformHandler.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::http;

class TrustedPlatformHandlerTest : public testing::Test {
public:
    TrustedPlatformHandler class_under_test;
};

TEST_F(TrustedPlatformHandlerTest, IsAuthenticatedAuthTokenIsNotEmptyOrWhitespaceReturnsTrue) {
    // Arrange
    const std::string auth_token("xyz");
    class_under_test.set_auth_token(auth_token);

    // Act
    bool actual = class_under_test.is_authenticated();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TrustedPlatformHandlerTest, IsAuthenticatedAuthTokenIsNotSetReturnsFalse) {
    // Act
    bool actual = class_under_test.is_authenticated();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TrustedPlatformHandlerTest, IsAuthenticatedAuthTokenIsEmptyReturnsFalse) {
    // Arrange
    const std::string auth_token;
    class_under_test.set_auth_token(auth_token);

    // Act
    bool actual = class_under_test.is_authenticated();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TrustedPlatformHandlerTest, IsAuthenticatedAuthTokenIsWhitespaceReturnsFalse) {
    // Arrange
    const std::string auth_token(" ");
    class_under_test.set_auth_token(auth_token);

    // Act
    bool actual = class_under_test.is_authenticated();

    // Assert
    ASSERT_FALSE(actual);
}
