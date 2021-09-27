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
#include "enjinsdk/models/SupplyModels.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class SupplyModelsTest : public JsonTestSuite,
                         public testing::Test {
public:
    SupplyModels class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"fixed":"1","settable":"1","infinite":"1","collapsing":"1","annualValue":"1","annualPercentage":"1"})";
};

TEST_F(SupplyModelsTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_fixed().has_value());
    EXPECT_FALSE(class_under_test.get_settable().has_value());
    EXPECT_FALSE(class_under_test.get_infinite().has_value());
    EXPECT_FALSE(class_under_test.get_collapsing().has_value());
    EXPECT_FALSE(class_under_test.get_annual_value().has_value());
    EXPECT_FALSE(class_under_test.get_annual_percentage().has_value());
}

TEST_F(SupplyModelsTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_fixed().has_value());
    EXPECT_FALSE(class_under_test.get_settable().has_value());
    EXPECT_FALSE(class_under_test.get_infinite().has_value());
    EXPECT_FALSE(class_under_test.get_collapsing().has_value());
    EXPECT_FALSE(class_under_test.get_annual_value().has_value());
    EXPECT_FALSE(class_under_test.get_annual_percentage().has_value());
}

TEST_F(SupplyModelsTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_fixed().value());
    EXPECT_EQ(expected_string, class_under_test.get_settable().value());
    EXPECT_EQ(expected_string, class_under_test.get_infinite().value());
    EXPECT_EQ(expected_string, class_under_test.get_collapsing().value());
    EXPECT_EQ(expected_string, class_under_test.get_annual_value().value());
    EXPECT_EQ(expected_string, class_under_test.get_annual_percentage().value());
}

TEST_F(SupplyModelsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SupplyModels lhs;
    SupplyModels rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SupplyModelsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SupplyModels lhs;
    SupplyModels rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SupplyModelsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SupplyModels lhs;
    SupplyModels rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SupplyModelsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SupplyModels lhs;
    SupplyModels rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
