#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TokenVariantModeTest : public testing::TestWithParam<std::tuple<std::string, TokenVariantMode>> {
};

TEST_P(TokenVariantModeTest, DeserializeTokenVariantModeReturnsExpectedValue) {
    // Arrange
    TokenVariantMode expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    TokenVariantMode actual = deserialize_token_variant_mode(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TokenVariantModeTest, SerializeTokenVariantModeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TokenVariantMode value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_token_variant_mode(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableTokenVariantMode,
                         TokenVariantModeTest,
                         testing::Values(std::make_tuple("UNKNOWN", TokenVariantMode::UNKNOWN),
                                         std::make_tuple("NONE", TokenVariantMode::NONE),
                                         std::make_tuple("BEAM", TokenVariantMode::BEAM),
                                         std::make_tuple("ONCE", TokenVariantMode::ONCE),
                                         std::make_tuple("ALWAYS", TokenVariantMode::ALWAYS)));
