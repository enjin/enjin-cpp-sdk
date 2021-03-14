#include "EnumUtils.hpp"
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
    std::string actual = serialize_asset_field(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeAssetField,
                         AssetFieldTest,
                         testing::Values(std::make_tuple("id", AssetField::ID),
                                         std::make_tuple("name", AssetField::NAME),
                                         std::make_tuple("circulatingSupply", AssetField::CIRCULATING_SUPPLY),
                                         std::make_tuple("nonFungible", AssetField::NON_FUNGIBLE),
                                         std::make_tuple("reserve", AssetField::RESERVE),
                                         std::make_tuple("totalSupply", AssetField::TOTAL_SUPPLY),
                                         std::make_tuple("createdAt", AssetField::CREATED_AT)));
