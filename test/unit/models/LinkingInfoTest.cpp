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
#include "enjinsdk/models/LinkingInfo.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class LinkingInfoTest : public JsonTestSuite,
                        public testing::Test {
public:
    LinkingInfo class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"code":"1","qr":"1"})";
};

TEST_F(LinkingInfoTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_code().has_value());
    EXPECT_FALSE(class_under_test.get_qr().has_value());
}

TEST_F(LinkingInfoTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_code().has_value());
    EXPECT_FALSE(class_under_test.get_qr().has_value());
}

TEST_F(LinkingInfoTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_code().value());
    EXPECT_EQ(expected_string, class_under_test.get_qr().value());
}

TEST_F(LinkingInfoTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    LinkingInfo lhs;
    LinkingInfo rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(LinkingInfoTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    LinkingInfo lhs;
    LinkingInfo rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(LinkingInfoTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    LinkingInfo lhs;
    LinkingInfo rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(LinkingInfoTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    LinkingInfo lhs;
    LinkingInfo rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
