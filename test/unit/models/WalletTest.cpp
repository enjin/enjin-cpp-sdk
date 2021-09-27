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
#include "enjinsdk/models/Wallet.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class WalletTest : public JsonTestSuite,
                   public testing::Test {
public:
    Wallet class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"ethAddress":"1","enjAllowance":1.0,"enjBalance":1.0,"ethBalance":1.0,"assetsCreated":[]})";
};

TEST_F(WalletTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_eth_address().has_value());
    EXPECT_FALSE(class_under_test.get_enj_allowance().has_value());
    EXPECT_FALSE(class_under_test.get_enj_balance().has_value());
    EXPECT_FALSE(class_under_test.get_eth_balance().has_value());
    EXPECT_FALSE(class_under_test.get_assets_created().has_value());
}

TEST_F(WalletTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_eth_address().has_value());
    EXPECT_FALSE(class_under_test.get_enj_allowance().has_value());
    EXPECT_FALSE(class_under_test.get_enj_balance().has_value());
    EXPECT_FALSE(class_under_test.get_eth_balance().has_value());
    EXPECT_FALSE(class_under_test.get_assets_created().has_value());
}

TEST_F(WalletTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const float expected_float = 1.0;
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_eth_address().value());
    EXPECT_EQ(expected_float, class_under_test.get_enj_allowance().value());
    EXPECT_EQ(expected_float, class_under_test.get_enj_balance().value());
    EXPECT_EQ(expected_float, class_under_test.get_eth_balance().value());
    EXPECT_TRUE(class_under_test.get_assets_created().has_value());
}

TEST_F(WalletTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Wallet lhs;
    Wallet rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(WalletTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Wallet lhs;
    Wallet rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(WalletTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Wallet lhs;
    Wallet rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(WalletTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Wallet lhs;
    Wallet rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
