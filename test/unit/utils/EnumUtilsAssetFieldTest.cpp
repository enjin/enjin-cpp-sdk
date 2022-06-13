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

#include "enjinsdk/EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class AssetFieldTest : public testing::TestWithParam<std::tuple<std::string, AssetField>> {
};

TEST_P(AssetFieldTest, SerializeAssetFieldReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetField value = std::get<1>(GetParam());

    // Act
    std::string actual = EnumUtils::serialize_asset_field(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeAssetField,
                         AssetFieldTest,
                         testing::Values(std::make_tuple("id", AssetField::Id),
                                         std::make_tuple("name", AssetField::Name),
                                         std::make_tuple("circulatingSupply", AssetField::CirculatingSupply),
                                         std::make_tuple("nonFungible", AssetField::NonFungible),
                                         std::make_tuple("reserve", AssetField::Reserve),
                                         std::make_tuple("totalSupply", AssetField::TotalSupply),
                                         std::make_tuple("createdAt", AssetField::CreatedAt)));
