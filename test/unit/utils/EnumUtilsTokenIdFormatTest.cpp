#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TokenIdFormatTest : public testing::TestWithParam<std::tuple<std::string, AssetIdFormat>> {
};

TEST_P(TokenIdFormatTest, SerializeTokenIdFormatReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    AssetIdFormat value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_asset_id_format(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeTokenIdFormat,
                         TokenIdFormatTest,
                         testing::Values(std::make_tuple("hex64", AssetIdFormat::HEX64),
                                         std::make_tuple("hex256", AssetIdFormat::HEX256),
                                         std::make_tuple("uint256", AssetIdFormat::UINT256)));
