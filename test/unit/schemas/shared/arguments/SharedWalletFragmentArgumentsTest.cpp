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
#include "TestableWalletFragmentArguments.hpp"
#include "WalletFragmentArgumentsTestSuite.hpp"
#include <string>

using namespace enjin::sdk::json;
using namespace enjin::test::suites;
using namespace enjin::test::utils;

class SharedWalletFragmentArgumentsTest
        : public JsonTestSuite,
          public WalletFragmentArgumentsTestSuite<TestableWalletFragmentArguments>,
          public testing::Test {
public:
    TestableWalletFragmentArguments class_under_test;

    static TestableWalletFragmentArguments create_default_arguments() {
        TestableWalletFragmentArguments arguments;
        set_asset_fragment_arguments(arguments);
        set_balance_fragment_arguments(arguments);
        set_transaction_fragment_arguments(arguments);
        set_wallet_fragment_arguments(arguments);
        return arguments;
    }
};

TEST_F(SharedWalletFragmentArgumentsTest, ToJsonNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const JsonValue expected = create_empty_json_object();

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedWalletFragmentArgumentsTest, ToJsonSetAssetFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = AssetFragmentArgumentsTestSuite::create_json_object();
    set_asset_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedWalletFragmentArgumentsTest, ToJsonSetBalanceFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = BalanceFragmentArgumentsTestSuite::create_json_object();
    set_balance_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedWalletFragmentArgumentsTest, ToJsonSetTransactionFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = TransactionFragmentArgumentsTestSuite::create_json_object();
    set_transaction_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedWalletFragmentArgumentsTest, ToJsonSetWalletFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const std::string expected(WalletFragmentJson);
    set_wallet_fragment_arguments(class_under_test);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedWalletFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    const TestableWalletFragmentArguments lhs;
    const TestableWalletFragmentArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedWalletFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    const TestableWalletFragmentArguments lhs = create_default_arguments();
    const TestableWalletFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedWalletFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableWalletFragmentArguments lhs = create_default_arguments();
    const TestableWalletFragmentArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedWalletFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableWalletFragmentArguments lhs;
    const TestableWalletFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
