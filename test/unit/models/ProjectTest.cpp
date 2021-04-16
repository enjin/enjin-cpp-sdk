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
#include "enjinsdk/models/Project.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class ProjectTest : public JsonTestSuite,
                    public testing::Test {
public:
    Project class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1,"name":"1","description":"1","image":"1","createdAt":"1","updatedAt":"1"})";
};

TEST_F(ProjectTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_description().has_value());
    EXPECT_FALSE(class_under_test.get_image().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(ProjectTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_description().has_value());
    EXPECT_FALSE(class_under_test.get_image().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(ProjectTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    const int expected_int = 1;
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_int, class_under_test.get_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_name().value());
    EXPECT_EQ(expected_string, class_under_test.get_description().value());
    EXPECT_EQ(expected_string, class_under_test.get_image().value());
    EXPECT_EQ(expected_string, class_under_test.get_created_at().value());
    EXPECT_EQ(expected_string, class_under_test.get_updated_at().value());
}

TEST_F(ProjectTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Project lhs;
    Project rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Project lhs;
    Project rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Project lhs;
    Project rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Project lhs;
    Project rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
