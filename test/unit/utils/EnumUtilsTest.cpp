#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TokenSupplyModelTest : public testing::TestWithParam<std::tuple<std::string, TokenSupplyModel>> {
};

class TokenTransferFeeTypeTest : public testing::TestWithParam<std::tuple<std::string, TokenTransferFeeType>> {
};

class TokenTransferableTest : public testing::TestWithParam<std::tuple<std::string, TokenTransferable>> {
};

class TokenVariantModeTest : public testing::TestWithParam<std::tuple<std::string, TokenVariantMode>> {
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
    std::string_view actual = serialize_token_supply_model(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

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
    std::string_view actual = serialize_token_transfer_fee_type(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

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
    std::string_view actual = serialize_token_transferable(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

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
    std::string_view actual = serialize_token_variant_mode(value);

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

INSTANTIATE_TEST_SUITE_P(SerializableTokenTransferFeeType,
                         TokenTransferFeeTypeTest,
                         testing::Values(std::make_tuple("UNKNOWN", TokenTransferFeeType::UNKNOWN),
                                         std::make_tuple("NONE", TokenTransferFeeType::NONE),
                                         std::make_tuple("PER_TRANSFER", TokenTransferFeeType::PER_TRANSFER),
                                         std::make_tuple("PER_CRYPTO_ITEM", TokenTransferFeeType::PER_CRYPTO_ITEM),
                                         std::make_tuple("RATIO_CUT", TokenTransferFeeType::RATIO_CUT),
                                         std::make_tuple("RATIO_EXTRA", TokenTransferFeeType::RATIO_EXTRA)));

INSTANTIATE_TEST_SUITE_P(SerializableTokenTransferable,
                         TokenTransferableTest,
                         testing::Values(std::make_tuple("UNKNOWN", TokenTransferable::UNKNOWN),
                                         std::make_tuple("PERMANENT", TokenTransferable::PERMANENT),
                                         std::make_tuple("TEMPORARY", TokenTransferable::TEMPORARY),
                                         std::make_tuple("BOUND", TokenTransferable::BOUND)));

INSTANTIATE_TEST_SUITE_P(SerializableTokenVariantMode,
                         TokenVariantModeTest,
                         testing::Values(std::make_tuple("UNKNOWN", TokenVariantMode::UNKNOWN),
                                         std::make_tuple("NONE", TokenVariantMode::NONE),
                                         std::make_tuple("BEAM", TokenVariantMode::BEAM),
                                         std::make_tuple("ONCE", TokenVariantMode::ONCE),
                                         std::make_tuple("ALWAYS", TokenVariantMode::ALWAYS)));
