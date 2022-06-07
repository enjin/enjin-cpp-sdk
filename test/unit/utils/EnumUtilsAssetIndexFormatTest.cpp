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

class AssetIndexFormatTest : public testing::TestWithParam<std::tuple<std::string, AssetIndexFormat>> {
};

TEST_P(AssetIndexFormatTest, SerializeAssetIndexFormatReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetIndexFormat value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_asset_index_format(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeAssetIndexFormat,
                         AssetIndexFormatTest,
                         testing::Values(std::make_tuple("hex64", AssetIndexFormat::Hex64),
                                         std::make_tuple("uint64", AssetIndexFormat::Uint64)));
