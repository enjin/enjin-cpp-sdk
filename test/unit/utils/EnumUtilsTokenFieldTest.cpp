#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TokenFieldTest : public testing::TestWithParam<std::tuple<std::string, TokenField>> {
};

TEST_P(TokenFieldTest, SerializeTokenFieldReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TokenField value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_token_field(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeTokenField,
                         TokenFieldTest,
                         testing::Values(std::make_tuple("id", TokenField::ID),
                                         std::make_tuple("name", TokenField::NAME),
                                         std::make_tuple("circulatingSupply", TokenField::CIRCULATING_SUPPLY),
                                         std::make_tuple("nonFungible", TokenField::NON_FUNGIBLE),
                                         std::make_tuple("reserve", TokenField::RESERVE),
                                         std::make_tuple("totalSupply", TokenField::TOTAL_SUPPLY),
                                         std::make_tuple("createdAt", TokenField::CREATED_AT)));
