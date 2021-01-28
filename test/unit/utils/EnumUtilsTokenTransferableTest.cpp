#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TokenTransferableTest : public testing::TestWithParam<std::tuple<std::string, TokenTransferable>> {
};

TEST_P(TokenTransferableTest, DeserializeTokenTransferableReturnsExpectedValue) {
    // Arrange
    TokenTransferable expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    TokenTransferable actual = deserialize_token_transferable(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TokenTransferableTest, SerializeTokenTransferableReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TokenTransferable value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_token_transferable(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableTokenTransferable,
                         TokenTransferableTest,
                         testing::Values(std::make_tuple("UNKNOWN", TokenTransferable::UNKNOWN),
                                         std::make_tuple("PERMANENT", TokenTransferable::PERMANENT),
                                         std::make_tuple("TEMPORARY", TokenTransferable::TEMPORARY),
                                         std::make_tuple("BOUND", TokenTransferable::BOUND)));
