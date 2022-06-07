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

TEST_F(SharedPlayerFragmentArgumentsTest, SerializeNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, SerializeSetAssetFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const std::string expected(AssetFragmentJson);
    set_asset_fragment_arguments(class_under_test);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, SerializeSetBalanceFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const std::string expected(BalanceFragmentJson);
    set_balance_fragment_arguments(class_under_test);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, SerializeSetPlayerFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const std::string expected(PlayerFragmentJson);
    set_player_fragment_arguments(class_under_test);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, SerializeSetTransactionFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const std::string expected(TransactionFragmentJson);
    set_transaction_fragment_arguments(class_under_test);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, SerializeSetWalletFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const std::string expected(WalletFragmentJson);
    set_wallet_fragment_arguments(class_under_test);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TestableSharedPlayerFragmentArguments lhs;
    TestableSharedPlayerFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TestableSharedPlayerFragmentArguments lhs = create_default_arguments();
    TestableSharedPlayerFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TestableSharedPlayerFragmentArguments lhs = create_default_arguments();
    TestableSharedPlayerFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedPlayerFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TestableSharedPlayerFragmentArguments lhs;
    TestableSharedPlayerFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
