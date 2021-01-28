#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TokenIdFormatTest : public testing::TestWithParam<std::tuple<std::string, TokenIdFormat>> {
};

TEST_P(TokenIdFormatTest, SerializeTokenIdFormatReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TokenIdFormat value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_token_id_format(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeTokenIdFormat,
                         TokenIdFormatTest,
                         testing::Values(std::make_tuple("hex64", TokenIdFormat::HEX64),
                                         std::make_tuple("hex256", TokenIdFormat::HEX256),
                                         std::make_tuple("uint256", TokenIdFormat::UINT256)));
