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
#include "TestableSharedTransactionFragmentArguments.hpp"
#include "TransactionFragmentArgumentsTestSuite.hpp"
#include <string>

using namespace enjin::sdk::json;
using namespace enjin::test::suites;
using namespace enjin::test::utils;

class SharedTransactionFragmentArgumentsTest
        : public JsonTestSuite,
          public TransactionFragmentArgumentsTestSuite<TestableSharedTransactionFragmentArguments>,
          public testing::Test {
public:
    TestableSharedTransactionFragmentArguments class_under_test;

    static TestableSharedTransactionFragmentArguments create_default_arguments() {
        TestableSharedTransactionFragmentArguments arguments;
        set_transaction_fragment_arguments(arguments);
        return arguments;
    }
};

TEST_F(SharedTransactionFragmentArgumentsTest, ToJsonNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const JsonValue expected = create_empty_json_object();

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, ToJsonSetTransactionFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = TransactionFragmentArgumentsTestSuite::create_json_object();
    set_transaction_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    const TestableSharedTransactionFragmentArguments lhs;
    const TestableSharedTransactionFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    const TestableSharedTransactionFragmentArguments lhs = create_default_arguments();
    const TestableSharedTransactionFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedTransactionFragmentArguments lhs = create_default_arguments();
    const TestableSharedTransactionFragmentArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedTransactionFragmentArguments lhs;
    const TestableSharedTransactionFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
