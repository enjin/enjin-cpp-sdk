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

TEST_F(SharedTransactionFragmentArgumentsTest, SerializeNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, SerializeSetTransactionFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const std::string expected(TransactionFragmentJson);
    set_transaction_fragment_arguments(class_under_test);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TestableSharedTransactionFragmentArguments lhs;
    TestableSharedTransactionFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TestableSharedTransactionFragmentArguments lhs = create_default_arguments();
    TestableSharedTransactionFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TestableSharedTransactionFragmentArguments lhs = create_default_arguments();
    TestableSharedTransactionFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedTransactionFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TestableSharedTransactionFragmentArguments lhs;
    TestableSharedTransactionFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
