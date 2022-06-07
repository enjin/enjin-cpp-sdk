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
#include "BalanceFragmentArgumentsTestSuite.hpp"
#include "JsonTestSuite.hpp"
#include "TestableSharedBalanceFragmentArguments.hpp"
#include <string>

using namespace enjin::sdk::json;
using namespace enjin::test::suites;
using namespace enjin::test::utils;

class SharedBalanceFragmentArgumentsTest
        : public BalanceFragmentArgumentsTestSuite<TestableSharedBalanceFragmentArguments>,
          public JsonTestSuite,
          public testing::Test {
public:
    TestableSharedBalanceFragmentArguments class_under_test;

    static TestableSharedBalanceFragmentArguments create_default_arguments() {
        TestableSharedBalanceFragmentArguments arguments;
        set_balance_fragment_arguments(arguments);
        return arguments;
    }
};

TEST_F(SharedBalanceFragmentArgumentsTest, ToJsonNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const JsonValue expected = create_empty_json_object();

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedBalanceFragmentArgumentsTest, ToJsonSetBalanceFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = BalanceFragmentArgumentsTestSuite::create_json_object();
    set_balance_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedBalanceFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    const TestableSharedBalanceFragmentArguments lhs;
    const TestableSharedBalanceFragmentArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedBalanceFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    const TestableSharedBalanceFragmentArguments lhs = create_default_arguments();
    const TestableSharedBalanceFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedBalanceFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedBalanceFragmentArguments lhs = create_default_arguments();
    const TestableSharedBalanceFragmentArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedBalanceFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedBalanceFragmentArguments lhs;
    const TestableSharedBalanceFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
