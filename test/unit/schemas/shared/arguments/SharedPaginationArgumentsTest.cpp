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

TEST_F(SharedPaginationArgumentsTest, SerializeNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPaginationArgumentsTest, SerializeSetPaginationFieldsReturnsExpectedJson) {
    // Arrange
    const std::string expected(PaginationJson);
    set_pagination_arguments(class_under_test);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPaginationArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TestableSharedPaginationArguments lhs;
    TestableSharedPaginationArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPaginationArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TestableSharedPaginationArguments lhs = create_default_arguments();
    TestableSharedPaginationArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPaginationArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TestableSharedPaginationArguments lhs = create_default_arguments();
    TestableSharedPaginationArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedPaginationArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TestableSharedPaginationArguments lhs;
    TestableSharedPaginationArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
