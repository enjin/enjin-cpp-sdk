/* Copyright 2021 Enjin Pte Ltd.
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
#include "enjinsdk/models/Asset.hpp"

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class AssetTest : public JsonTestSuite,
                  public testing::Test {
public:
    Asset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1","name":"1","stateData":{},"configData":{},"variantMode":"NONE","variants":[{}, {}, {}],"createdAt":"1","updatedAt":"1"})";
};

TEST_F(AssetTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_state_data().has_value());
    EXPECT_FALSE(class_under_test.get_config_data().has_value());
    EXPECT_FALSE(class_under_test.get_variant_mode().has_value());
    EXPECT_FALSE(class_under_test.get_variants().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(AssetTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_state_data().has_value());
    EXPECT_FALSE(class_under_test.get_config_data().has_value());
    EXPECT_FALSE(class_under_test.get_variant_mode().has_value());
    EXPECT_FALSE(class_under_test.get_variants().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(AssetTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const AssetStateData expected_state_data;
    const AssetConfigData expected_config_data;
    const AssetVariantMode expected_variant_mode = AssetVariantMode::NONE;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_name().value());
    EXPECT_EQ(expected_state_data, class_under_test.get_state_data().value());
    EXPECT_EQ(expected_config_data, class_under_test.get_config_data().value());
    EXPECT_EQ(expected_variant_mode, class_under_test.get_variant_mode().value());
    EXPECT_TRUE(class_under_test.get_variants().has_value());
    EXPECT_FALSE(class_under_test.get_variants().value().empty());
    EXPECT_EQ(expected_string, class_under_test.get_created_at().value());
    EXPECT_EQ(expected_string, class_under_test.get_updated_at().value());
}

TEST_F(AssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Asset lhs;
    Asset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Asset lhs;
    Asset rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Asset lhs;
    Asset rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Asset lhs;
    Asset rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
