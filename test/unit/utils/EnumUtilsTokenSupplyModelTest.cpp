#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TokenSupplyModelTest : public testing::TestWithParam<std::tuple<std::string, AssetSupplyModel>> {
};

TEST_P(TokenSupplyModelTest, DeserializeTokenSupplyModelReturnsExpectedValue) {
    // Arrange
    AssetSupplyModel expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    AssetSupplyModel actual = deserialize_asset_supply_model(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TokenSupplyModelTest, SerializeTokenSupplyModelReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetSupplyModel value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_asset_supply_model(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableTokenSupplyModel,
                         TokenSupplyModelTest,
                         testing::Values(std::make_tuple("UNKNOWN", AssetSupplyModel::UNKNOWN),
                                         std::make_tuple("FIXED", AssetSupplyModel::FIXED),
                                         std::make_tuple("SETTABLE", AssetSupplyModel::SETTABLE),
                                         std::make_tuple("INFINITE", AssetSupplyModel::INFINITE),
                                         std::make_tuple("COLLAPSING", AssetSupplyModel::COLLAPSING),
                                         std::make_tuple("ANNUAL_VALUE", AssetSupplyModel::ANNUAL_VALUE),
                                         std::make_tuple("ANNUAL_PERCENTAGE", AssetSupplyModel::ANNUAL_PERCENTAGE)));
