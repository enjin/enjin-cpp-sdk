#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TokenTransferFeeTypeTest : public testing::TestWithParam<std::tuple<std::string, TokenTransferFeeType>> {
};

TEST_P(TokenTransferFeeTypeTest, DeserializeTokenTransferFeeTypeReturnsExpectedValue) {
    // Arrange
    TokenTransferFeeType expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    TokenTransferFeeType actual = deserialize_token_transfer_fee_type(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TokenTransferFeeTypeTest, SerializeTokenTransferFeeTypeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TokenTransferFeeType value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_token_transfer_fee_type(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableTokenTransferFeeType,
                         TokenTransferFeeTypeTest,
                         testing::Values(std::make_tuple("UNKNOWN", TokenTransferFeeType::UNKNOWN),
                                         std::make_tuple("NONE", TokenTransferFeeType::NONE),
                                         std::make_tuple("PER_TRANSFER", TokenTransferFeeType::PER_TRANSFER),
                                         std::make_tuple("PER_CRYPTO_ITEM", TokenTransferFeeType::PER_CRYPTO_ITEM),
                                         std::make_tuple("RATIO_CUT", TokenTransferFeeType::RATIO_CUT),
                                         std::make_tuple("RATIO_EXTRA", TokenTransferFeeType::RATIO_EXTRA)));
