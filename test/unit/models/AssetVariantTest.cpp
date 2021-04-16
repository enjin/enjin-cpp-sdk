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
#include "enjinsdk/models/AssetVariant.hpp"

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class AssetVariantTest : public JsonTestSuite,
                         public testing::Test {
public:
    AssetVariant class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1,"assetId":"1","variantMetadata":"{}","usageCount":1,"createdAt":"1","updatedAt":"1"})";
};

TEST_F(AssetVariantTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_asset_id().has_value());
    EXPECT_FALSE(class_under_test.get_variant_metadata().has_value());
    EXPECT_FALSE(class_under_test.get_usage_count().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(AssetVariantTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_asset_id().has_value());
    EXPECT_FALSE(class_under_test.get_variant_metadata().has_value());
    EXPECT_FALSE(class_under_test.get_usage_count().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(AssetVariantTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const int expected_id = 1;
    const std::string expected_asset_id("1");
    const std::string expected_variant_metadata("{}");
    const int expected_usage_count = 1;
    const std::string expected_created_at("1");
    const std::string expected_updated_at("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_id, class_under_test.get_id().value());
    EXPECT_EQ(expected_asset_id, class_under_test.get_asset_id().value());
    EXPECT_EQ(expected_variant_metadata, class_under_test.get_variant_metadata().value());
    EXPECT_EQ(expected_usage_count, class_under_test.get_usage_count().value());
    EXPECT_EQ(expected_created_at, class_under_test.get_created_at().value());
    EXPECT_EQ(expected_updated_at, class_under_test.get_updated_at().value());
}

TEST_F(AssetVariantTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AssetVariant lhs;
    AssetVariant rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetVariantTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AssetVariant lhs;
    AssetVariant rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetVariantTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetVariant lhs;
    AssetVariant rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AssetVariantTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetVariant lhs;
    AssetVariant rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
