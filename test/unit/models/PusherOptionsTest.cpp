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
#include "JsonTestSuite.hpp"
#include "enjinsdk/models/PusherOptions.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class PusherOptionsTest : public JsonTestSuite,
                          public testing::Test {
public:
    PusherOptions class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"cluster":"1","encrypted":true})";
};

TEST_F(PusherOptionsTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_cluster().has_value());
    EXPECT_FALSE(class_under_test.get_encrypted().has_value());
}

TEST_F(PusherOptionsTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EmptyJsonObject);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_cluster().has_value());
    EXPECT_FALSE(class_under_test.get_encrypted().has_value());
}

TEST_F(PusherOptionsTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const bool expected_bool = true;
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_cluster().value());
    EXPECT_EQ(expected_bool, class_under_test.get_encrypted().value());
}

TEST_F(PusherOptionsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PusherOptions lhs;
    PusherOptions rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherOptionsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PusherOptions lhs;
    PusherOptions rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherOptionsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PusherOptions lhs;
    PusherOptions rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PusherOptionsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PusherOptions lhs;
    PusherOptions rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
