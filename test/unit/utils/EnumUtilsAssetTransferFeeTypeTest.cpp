#include "EnumUtils.hpp"
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
    AssetTransferFeeType actual = deserialize_asset_transfer_fee_type(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(AssetTransferFeeTypeTest, SerializeAssetTransferFeeTypeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetTransferFeeType value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_asset_transfer_fee_type(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableAssetTransferFeeType,
                         AssetTransferFeeTypeTest,
                         testing::Values(std::make_tuple("UNKNOWN", AssetTransferFeeType::UNKNOWN),
                                         std::make_tuple("NONE", AssetTransferFeeType::NONE),
                                         std::make_tuple("PER_TRANSFER", AssetTransferFeeType::PER_TRANSFER),
                                         std::make_tuple("PER_CRYPTO_ITEM", AssetTransferFeeType::PER_CRYPTO_ITEM),
                                         std::make_tuple("RATIO_CUT", AssetTransferFeeType::RATIO_CUT),
                                         std::make_tuple("RATIO_EXTRA", AssetTransferFeeType::RATIO_EXTRA)));
