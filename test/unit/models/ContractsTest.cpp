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
#include "enjinsdk/models/Contracts.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class ContractsTest : public JsonTestSuite,
                      public testing::Test {
public:
    Contracts class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"enj":"1","cryptoItems":"1","platformRegistry":"1","supplyModels":{}})";
};

TEST_F(ContractsTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_enj().has_value());
    EXPECT_FALSE(class_under_test.get_crypto_items().has_value());
    EXPECT_FALSE(class_under_test.get_platform_registry().has_value());
    EXPECT_FALSE(class_under_test.get_supply_models().has_value());
}

TEST_F(ContractsTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_enj().has_value());
    EXPECT_FALSE(class_under_test.get_crypto_items().has_value());
    EXPECT_FALSE(class_under_test.get_platform_registry().has_value());
    EXPECT_FALSE(class_under_test.get_supply_models().has_value());
}

TEST_F(ContractsTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const SupplyModels expected_supply_models;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_enj().value());
    EXPECT_EQ(expected_string, class_under_test.get_crypto_items().value());
    EXPECT_EQ(expected_string, class_under_test.get_platform_registry().value());
    EXPECT_EQ(expected_supply_models, class_under_test.get_supply_models().value());
}

TEST_F(ContractsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Contracts lhs;
    Contracts rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ContractsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Contracts lhs;
    Contracts rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ContractsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Contracts lhs;
    Contracts rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ContractsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Contracts lhs;
    Contracts rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
