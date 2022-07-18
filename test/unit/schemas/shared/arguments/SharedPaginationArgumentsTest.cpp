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
#include "PaginationArgumentsTestSuite.hpp"
#include "TestableSharedPaginationArguments.hpp"
#include <string>

using namespace enjin::sdk::json;
using namespace enjin::test::suites;
using namespace enjin::test::utils;

class SharedPaginationArgumentsTest
        : public JsonTestSuite,
          public PaginationArgumentsTestSuite<TestableSharedPaginationArguments>,
          public testing::Test {
public:
    TestableSharedPaginationArguments class_under_test;

    static TestableSharedPaginationArguments create_default_arguments() {
        TestableSharedPaginationArguments arguments;
        set_pagination_arguments(arguments);
        return arguments;
    }
};

TEST_F(SharedPaginationArgumentsTest, ToJsonNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const JsonValue expected = create_empty_json_object();

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPaginationArgumentsTest, ToJsonSetPaginationFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = PaginationArgumentsTestSuite::create_json_object();
    set_pagination_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPaginationArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    const TestableSharedPaginationArguments lhs;
    const TestableSharedPaginationArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPaginationArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    const TestableSharedPaginationArguments lhs = create_default_arguments();
    const TestableSharedPaginationArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPaginationArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedPaginationArguments lhs = create_default_arguments();
    const TestableSharedPaginationArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedPaginationArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedPaginationArguments lhs;
    const TestableSharedPaginationArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
