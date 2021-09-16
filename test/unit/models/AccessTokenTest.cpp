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

#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/models/AccessToken.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class AccessTokenTest : public JsonTestSuite,
                        public testing::Test {
public:
    AccessToken class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"accessToken":"xyz","expiresIn":1})";
};

TEST_F(AccessTokenTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_token().has_value());
    EXPECT_FALSE(class_under_test.get_expires_in().has_value());
}

TEST_F(AccessTokenTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_token().has_value());
    EXPECT_FALSE(class_under_test.get_expires_in().has_value());
}

TEST_F(AccessTokenTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_token("xyz");
    const long expected_expires_in = 1;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_token, class_under_test.get_token().value());
    EXPECT_EQ(expected_expires_in, class_under_test.get_expires_in().value());
}

TEST_F(AccessTokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AccessToken lhs;
    AccessToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AccessTokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AccessToken lhs;
    AccessToken rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AccessTokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AccessToken lhs;
    AccessToken rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AccessTokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AccessToken lhs;
    AccessToken rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
