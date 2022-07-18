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
#include "enjinsdk/models/AssetTransferFeeSettingsInput.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class AssetTransferFeeSettingsInputTest : public JsonTestSuite,
                                          public testing::Test {
public:
    AssetTransferFeeSettingsInput class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"type":"NONE","assetId":"1","value":"1"})";

    static AssetTransferFeeSettingsInput create_default_transfer_fee_settings_input() {
        return AssetTransferFeeSettingsInput().set_type(AssetTransferFeeType::None)
                                              .set_asset_id("1")
                                              .set_value("1");
    }
};

TEST_F(AssetTransferFeeSettingsInputTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetTransferFeeSettingsInputTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_type(AssetTransferFeeType::None)
                    .set_asset_id("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetTransferFeeSettingsInputTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AssetTransferFeeSettingsInput lhs;
    AssetTransferFeeSettingsInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetTransferFeeSettingsInputTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AssetTransferFeeSettingsInput lhs = create_default_transfer_fee_settings_input();
    AssetTransferFeeSettingsInput rhs = create_default_transfer_fee_settings_input();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetTransferFeeSettingsInputTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetTransferFeeSettingsInput lhs = create_default_transfer_fee_settings_input();
    AssetTransferFeeSettingsInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AssetTransferFeeSettingsInputTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetTransferFeeSettingsInput lhs;
    AssetTransferFeeSettingsInput rhs = create_default_transfer_fee_settings_input();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
