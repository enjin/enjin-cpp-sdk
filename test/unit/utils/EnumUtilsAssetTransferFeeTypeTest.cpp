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

class AssetTransferFeeTypeTest : public testing::TestWithParam<std::tuple<std::string, AssetTransferFeeType>> {
};

TEST_P(AssetTransferFeeTypeTest, DeserializeAssetTransferFeeTypeReturnsExpectedValue) {
    // Arrange
    AssetTransferFeeType expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    AssetTransferFeeType actual = EnumUtils::deserialize_asset_transfer_fee_type(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(AssetTransferFeeTypeTest, SerializeAssetTransferFeeTypeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetTransferFeeType value = std::get<1>(GetParam());

    // Act
    std::string actual = EnumUtils::serialize_asset_transfer_fee_type(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableAssetTransferFeeType,
                         AssetTransferFeeTypeTest,
                         testing::Values(std::make_tuple("UNKNOWN", AssetTransferFeeType::Unknown),
                                         std::make_tuple("NONE", AssetTransferFeeType::None),
                                         std::make_tuple("PER_TRANSFER", AssetTransferFeeType::PerTransfer),
                                         std::make_tuple("PER_CRYPTO_ITEM", AssetTransferFeeType::PerCryptoItem),
                                         std::make_tuple("RATIO_CUT", AssetTransferFeeType::RatioCut),
                                         std::make_tuple("RATIO_EXTRA", AssetTransferFeeType::RatioExtra)));
