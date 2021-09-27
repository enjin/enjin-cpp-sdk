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
#include "enjinsdk/internal/BalanceFragmentArgumentsImpl.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SharedBalanceFragmentArgumentsImplTest : public JsonTestSuite,
                                               public testing::Test {
public:
    BalanceFragmentArgumentsImpl class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"balIdFormat":"hex64","balIndexFormat":"hex64","withBalProjectUuid":true,"withBalWalletAddress":true})";

    static BalanceFragmentArgumentsImpl create_default_arguments() {
        BalanceFragmentArgumentsImpl arguments;
        arguments.set_bal_id_format(AssetIdFormat::HEX64);
        arguments.set_bal_index_format(AssetIndexFormat::HEX64);
        arguments.set_with_bal_project_uuid();
        arguments.set_with_bal_wallet_address();
        return arguments;
    }
};

TEST_F(SharedBalanceFragmentArgumentsImplTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedBalanceFragmentArgumentsImplTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_bal_id_format(AssetIdFormat::HEX64);
    class_under_test.set_bal_index_format(AssetIndexFormat::HEX64);
    class_under_test.set_with_bal_project_uuid();
    class_under_test.set_with_bal_wallet_address();

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedBalanceFragmentArgumentsImplTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    BalanceFragmentArgumentsImpl lhs;
    BalanceFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedBalanceFragmentArgumentsImplTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    BalanceFragmentArgumentsImpl lhs = create_default_arguments();
    BalanceFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedBalanceFragmentArgumentsImplTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    BalanceFragmentArgumentsImpl lhs = create_default_arguments();
    BalanceFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedBalanceFragmentArgumentsImplTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    BalanceFragmentArgumentsImpl lhs;
    BalanceFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
