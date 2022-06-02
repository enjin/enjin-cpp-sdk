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

class AssetVariantModeTest : public testing::TestWithParam<std::tuple<std::string, AssetVariantMode>> {
};

TEST_P(AssetVariantModeTest, DeserializeAssetVariantModeReturnsExpectedValue) {
    // Arrange
    AssetVariantMode expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    AssetVariantMode actual = EnumUtils::deserialize_asset_variant_mode(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(AssetVariantModeTest, SerializeAssetVariantModeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetVariantMode value = std::get<1>(GetParam());

    // Act
    std::string actual = EnumUtils::serialize_asset_variant_mode(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableAssetVariantMode,
                         AssetVariantModeTest,
                         testing::Values(std::make_tuple("UNKNOWN", AssetVariantMode::Unknown),
                                         std::make_tuple("NONE", AssetVariantMode::None),
                                         std::make_tuple("BEAM", AssetVariantMode::Beam),
                                         std::make_tuple("ONCE", AssetVariantMode::Once),
                                         std::make_tuple("ALWAYS", AssetVariantMode::Always)));
