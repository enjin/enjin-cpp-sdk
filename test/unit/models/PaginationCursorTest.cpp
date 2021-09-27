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
#include "enjinsdk/models/PaginationCursor.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class PaginationCursorTest : public JsonTestSuite,
                             public testing::Test {
public:
    PaginationCursor class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"total":1,"perPage":1,"currentPage":1,"hasPages":true,"from":1,"to":1,"lastPage":1,"hasMorePages":true})";
};

TEST_F(PaginationCursorTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_total().has_value());
    EXPECT_FALSE(class_under_test.get_per_page().has_value());
    EXPECT_FALSE(class_under_test.get_current_page().has_value());
    EXPECT_FALSE(class_under_test.get_has_pages().has_value());
    EXPECT_FALSE(class_under_test.get_from().has_value());
    EXPECT_FALSE(class_under_test.get_to().has_value());
    EXPECT_FALSE(class_under_test.get_last_page().has_value());
    EXPECT_FALSE(class_under_test.get_has_more_pages().has_value());
}

TEST_F(PaginationCursorTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_total().has_value());
    EXPECT_FALSE(class_under_test.get_per_page().has_value());
    EXPECT_FALSE(class_under_test.get_current_page().has_value());
    EXPECT_FALSE(class_under_test.get_has_pages().has_value());
    EXPECT_FALSE(class_under_test.get_from().has_value());
    EXPECT_FALSE(class_under_test.get_to().has_value());
    EXPECT_FALSE(class_under_test.get_last_page().has_value());
    EXPECT_FALSE(class_under_test.get_has_more_pages().has_value());
}

TEST_F(PaginationCursorTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const int expected_int = 1;
    const bool expected_bool = true;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_int, class_under_test.get_total().value());
    EXPECT_EQ(expected_int, class_under_test.get_per_page().value());
    EXPECT_EQ(expected_int, class_under_test.get_current_page().value());
    EXPECT_EQ(expected_bool, class_under_test.get_has_pages().value());
    EXPECT_EQ(expected_int, class_under_test.get_from().value());
    EXPECT_EQ(expected_int, class_under_test.get_to().value());
    EXPECT_EQ(expected_int, class_under_test.get_last_page().value());
    EXPECT_EQ(expected_bool, class_under_test.get_has_more_pages().value());
}

TEST_F(PaginationCursorTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PaginationCursor lhs;
    PaginationCursor rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationCursorTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PaginationCursor lhs;
    PaginationCursor rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationCursorTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationCursor lhs;
    PaginationCursor rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PaginationCursorTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationCursor lhs;
    PaginationCursor rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
