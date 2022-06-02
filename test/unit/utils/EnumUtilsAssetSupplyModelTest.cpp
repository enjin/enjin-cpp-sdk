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

#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class AssetSupplyModelTest : public testing::TestWithParam<std::tuple<std::string, AssetSupplyModel>> {
};

TEST_P(AssetSupplyModelTest, DeserializeAssetSupplyModelReturnsExpectedValue) {
    // Arrange
    AssetSupplyModel expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    AssetSupplyModel actual = deserialize_asset_supply_model(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(AssetSupplyModelTest, SerializeAssetSupplyModelReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetSupplyModel value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_asset_supply_model(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableAssetSupplyModel,
                         AssetSupplyModelTest,
                         testing::Values(std::make_tuple("UNKNOWN", AssetSupplyModel::Unknown),
                                         std::make_tuple("FIXED", AssetSupplyModel::Fixed),
                                         std::make_tuple("SETTABLE", AssetSupplyModel::Settable),
                                         std::make_tuple("INFINITE", AssetSupplyModel::Infinite),
                                         std::make_tuple("COLLAPSING", AssetSupplyModel::Collapsing),
                                         std::make_tuple("ANNUAL_VALUE", AssetSupplyModel::AnnualValue),
                                         std::make_tuple("ANNUAL_PERCENTAGE", AssetSupplyModel::AnnualPercentage)));
