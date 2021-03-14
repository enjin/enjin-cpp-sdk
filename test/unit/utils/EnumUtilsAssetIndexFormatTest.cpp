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
                         testing::Values(std::make_tuple("hex64", AssetIndexFormat::HEX64),
                                         std::make_tuple("uint64", AssetIndexFormat::UINT64)));
