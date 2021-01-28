#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TokenSupplyModelTest : public testing::TestWithParam<std::tuple<std::string, TokenSupplyModel>> {
};

TEST_P(TokenSupplyModelTest, DeserializeTokenSupplyModelReturnsExpectedValue) {
    // Arrange
    TokenSupplyModel expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    TokenSupplyModel actual = deserialize_token_supply_model(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TokenSupplyModelTest, SerializeTokenSupplyModelReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TokenSupplyModel value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_token_supply_model(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableTokenSupplyModel,
                         TokenSupplyModelTest,
                         testing::Values(std::make_tuple("UNKNOWN", TokenSupplyModel::UNKNOWN),
                                         std::make_tuple("FIXED", TokenSupplyModel::FIXED),
                                         std::make_tuple("SETTABLE", TokenSupplyModel::SETTABLE),
                                         std::make_tuple("INFINITE", TokenSupplyModel::INFINITE),
                                         std::make_tuple("COLLAPSING", TokenSupplyModel::COLLAPSING),
                                         std::make_tuple("ANNUAL_VALUE", TokenSupplyModel::ANNUAL_VALUE),
                                         std::make_tuple("ANNUAL_PERCENTAGE", TokenSupplyModel::ANNUAL_PERCENTAGE)));
