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

#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class AssetTransferableTest : public testing::TestWithParam<std::tuple<std::string, AssetTransferable>> {
};

TEST_P(AssetTransferableTest, DeserializeAssetTransferableReturnsExpectedValue) {
    // Arrange
    AssetTransferable expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    AssetTransferable actual = deserialize_asset_transferable(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(AssetTransferableTest, SerializeAssetTransferableReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetTransferable value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_asset_transferable(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableAssetTransferable,
                         AssetTransferableTest,
                         testing::Values(std::make_tuple("UNKNOWN", AssetTransferable::UNKNOWN),
                                         std::make_tuple("PERMANENT", AssetTransferable::PERMANENT),
                                         std::make_tuple("TEMPORARY", AssetTransferable::TEMPORARY),
                                         std::make_tuple("BOUND", AssetTransferable::BOUND)));
