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
#include "PlayerFragmentArgumentsTestSuite.hpp"
#include "TestableSharedPlayerFragmentArguments.hpp"
#include <string>

using namespace enjin::sdk::json;
using namespace enjin::test::suites;
using namespace enjin::test::utils;

class SharedPlayerFragmentArgumentsTest
        : public JsonTestSuite,
          public PlayerFragmentArgumentsTestSuite<TestableSharedPlayerFragmentArguments>,
          public testing::Test {
public:
    TestableSharedPlayerFragmentArguments class_under_test;

    static TestableSharedPlayerFragmentArguments create_default_arguments() {
        TestableSharedPlayerFragmentArguments arguments;
        set_asset_fragment_arguments(arguments);
        set_balance_fragment_arguments(arguments);
        set_player_fragment_arguments(arguments);
        set_transaction_fragment_arguments(arguments);
        set_wallet_fragment_arguments(arguments);
        return arguments;
    }
};

TEST_F(SharedPlayerFragmentArgumentsTest, ToJsonNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const JsonValue expected = create_empty_json_object();

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, ToJsonSetAssetFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = AssetFragmentArgumentsTestSuite::create_json_object();
    set_asset_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, ToJsonSetBalanceFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = BalanceFragmentArgumentsTestSuite::create_json_object();
    set_balance_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, ToJsonSetPlayerFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = PlayerFragmentArgumentsTestSuite::create_json_object();
    set_player_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, ToJsonSetTransactionFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = TransactionFragmentArgumentsTestSuite::create_json_object();
    set_transaction_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, ToJsonSetWalletFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = WalletFragmentArgumentsTestSuite::create_json_object();
    set_wallet_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    const TestableSharedPlayerFragmentArguments lhs;
    const TestableSharedPlayerFragmentArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    const TestableSharedPlayerFragmentArguments lhs = create_default_arguments();
    const TestableSharedPlayerFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedPlayerFragmentArguments lhs = create_default_arguments();
    const TestableSharedPlayerFragmentArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedPlayerFragmentArguments lhs;
    const TestableSharedPlayerFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
