#include "EnumUtils.hpp"
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
    AssetVariantMode actual = deserialize_asset_variant_mode(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(AssetVariantModeTest, SerializeAssetVariantModeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetVariantMode value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_asset_variant_mode(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableAssetVariantMode,
                         AssetVariantModeTest,
                         testing::Values(std::make_tuple("UNKNOWN", AssetVariantMode::UNKNOWN),
                                         std::make_tuple("NONE", AssetVariantMode::NONE),
                                         std::make_tuple("BEAM", AssetVariantMode::BEAM),
                                         std::make_tuple("ONCE", AssetVariantMode::ONCE),
                                         std::make_tuple("ALWAYS", AssetVariantMode::ALWAYS)));
