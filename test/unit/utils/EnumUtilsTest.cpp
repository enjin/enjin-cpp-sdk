#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class RequestStateTest : public testing::TestWithParam<std::tuple<std::string, RequestState>> {
};

class RequestTypeTest : public testing::TestWithParam<std::tuple<std::string, RequestType>> {
};

class SortDirectionTest : public testing::TestWithParam<std::tuple<std::string, SortDirection>> {
};

class TokenFieldTest : public testing::TestWithParam<std::tuple<std::string, TokenField>> {
};

class TokenIdFormatTest : public testing::TestWithParam<std::tuple<std::string, TokenIdFormat>> {
};

class TokenIndexFormatTest : public testing::TestWithParam<std::tuple<std::string, TokenIndexFormat>> {
};

class TokenSupplyModelTest : public testing::TestWithParam<std::tuple<std::string, TokenSupplyModel>> {
};

class TokenTransferFeeTypeTest : public testing::TestWithParam<std::tuple<std::string, TokenTransferFeeType>> {
};

class TokenTransferableTest : public testing::TestWithParam<std::tuple<std::string, TokenTransferable>> {
};

class TokenVariantModeTest : public testing::TestWithParam<std::tuple<std::string, TokenVariantMode>> {
};

class TransactionFieldTest : public testing::TestWithParam<std::tuple<std::string, TransactionField>> {
};

class WhitelistedTest : public testing::TestWithParam<std::tuple<std::string, Whitelisted>> {
};

TEST_P(RequestStateTest, DeserializeRequestStateReturnsExpectedValue) {
    // Arrange
    RequestState expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    RequestState actual = deserialize_request_state(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(RequestStateTest, SerializeRequestStateReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    RequestState value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_request_state(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(RequestTypeTest, DeserializeRequestTypeReturnsExpectedValue) {
    // Arrange
    RequestType expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    RequestType actual = deserialize_request_type(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(RequestTypeTest, SerializeRequestTypeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    RequestType value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_request_type(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(SortDirectionTest, SerializeSortDirectionReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    SortDirection value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_sort_direction(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TokenFieldTest, SerializeTokenFieldReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TokenField value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_token_field(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TokenIdFormatTest, SerializeTokenIdFormatReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TokenIdFormat value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_token_id_format(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TokenIndexFormatTest, SerializeTokenIndexFormatReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TokenIndexFormat value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_token_index_format(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

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

TEST_P(TransactionFieldTest, SerializeTransactionFieldReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TransactionField value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_transaction_field(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(WhitelistedTest, SerializeWhitelistedReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    Whitelisted value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_whitelisted(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableRequestState,
                         RequestStateTest,
                         testing::Values(std::make_tuple("PENDING", RequestState::PENDING),
                                         std::make_tuple("BROADCAST", RequestState::BROADCAST),
                                         std::make_tuple("TP_PROCESSING", RequestState::TP_PROCESSING),
                                         std::make_tuple("EXECUTED", RequestState::EXECUTED),
                                         std::make_tuple("CANCELED_USER", RequestState::CANCELED_USER),
                                         std::make_tuple("CANCELED_PLATFORM", RequestState::CANCELED_PLATFORM),
                                         std::make_tuple("DROPPED", RequestState::DROPPED),
                                         std::make_tuple("FAILED", RequestState::FAILED),
                                         std::make_tuple("", RequestState::UNKNOWN)));

INSTANTIATE_TEST_SUITE_P(SerializableRequestType,
                         RequestTypeTest,
                         testing::Values(std::make_tuple("APPROVE", RequestType::APPROVE),
                                         std::make_tuple("CREATE", RequestType::CREATE),
                                         std::make_tuple("MINT", RequestType::MINT),
                                         std::make_tuple("SEND", RequestType::SEND),
                                         std::make_tuple("SEND_ENJ", RequestType::SEND_ENJ),
                                         std::make_tuple("ADVANCED_SEND", RequestType::ADVANCED_SEND),
                                         std::make_tuple("CREATE_TRADE", RequestType::CREATE_TRADE),
                                         std::make_tuple("CANCEL_TRADE", RequestType::CANCEL_TRADE),
                                         std::make_tuple("MELT", RequestType::MELT),
                                         std::make_tuple("UPDATE_NAME", RequestType::UPDATE_NAME),
                                         std::make_tuple("SET_ITEM_URI", RequestType::SET_ITEM_URI),
                                         std::make_tuple("SET_WHITELISTED", RequestType::SET_WHITELISTED),
                                         std::make_tuple("SET_TRANSFERABLE", RequestType::SET_TRANSFERABLE),
                                         std::make_tuple("SET_MELT_FEE", RequestType::SET_MELT_FEE),
                                         std::make_tuple("DECREASE_MAX_MELT_FEE", RequestType::DECREASE_MAX_MELT_FEE),
                                         std::make_tuple("SET_TRANSFER_FEE", RequestType::SET_TRANSFER_FEE),
                                         std::make_tuple("DECREASE_MAX_TRANSFER_FEE",
                                                         RequestType::DECREASE_MAX_TRANSFER_FEE),
                                         std::make_tuple("RELEASE_RESERVE", RequestType::RELEASE_RESERVE),
                                         std::make_tuple("ADD_LOG", RequestType::ADD_LOG),
                                         std::make_tuple("SET_APPROVAL_FOR_ALL", RequestType::SET_APPROVAL_FOR_ALL),
                                         std::make_tuple("MANAGE_UPDATE", RequestType::MANAGE_UPDATE),
                                         std::make_tuple("SET_DECIMALS", RequestType::SET_DECIMALS),
                                         std::make_tuple("SET_SYMBOL", RequestType::SET_SYMBOL),
                                         std::make_tuple("MESSAGE", RequestType::MESSAGE),
                                         std::make_tuple("", RequestType::UNKNOWN)));

INSTANTIATE_TEST_SUITE_P(SerializeSortDirection,
                         SortDirectionTest,
                         testing::Values(std::make_tuple("asc", SortDirection::ASCENDING),
                                         std::make_tuple("desc", SortDirection::DESCENDING)));

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

INSTANTIATE_TEST_SUITE_P(SerializeTokenField,
                         TokenFieldTest,
                         testing::Values(std::make_tuple("id", TokenField::ID),
                                         std::make_tuple("name", TokenField::NAME),
                                         std::make_tuple("circulatingSupply", TokenField::CIRCULATING_SUPPLY),
                                         std::make_tuple("nonFungible", TokenField::NON_FUNGIBLE),
                                         std::make_tuple("reserve", TokenField::RESERVE),
                                         std::make_tuple("totalSupply", TokenField::TOTAL_SUPPLY),
                                         std::make_tuple("createdAt", TokenField::CREATED_AT)));

INSTANTIATE_TEST_SUITE_P(SerializeTokenIdFormat,
                         TokenIdFormatTest,
                         testing::Values(std::make_tuple("hex64", TokenIdFormat::HEX64),
                                         std::make_tuple("hex256", TokenIdFormat::HEX256),
                                         std::make_tuple("uint256", TokenIdFormat::UINT256)));

INSTANTIATE_TEST_SUITE_P(SerializeTokenIndexFormat,
                         TokenIndexFormatTest,
                         testing::Values(std::make_tuple("hex64", TokenIndexFormat::HEX64),
                                         std::make_tuple("uint64", TokenIndexFormat::UINT64)));

INSTANTIATE_TEST_SUITE_P(SerializeTransactionField,
                         TransactionFieldTest,
                         testing::Values(std::make_tuple("id", TransactionField::ID),
                                         std::make_tuple("state", TransactionField::STATE),
                                         std::make_tuple("title", TransactionField::TITLE),
                                         std::make_tuple("createdAt", TransactionField::CREATED_AT)));

INSTANTIATE_TEST_SUITE_P(SerializeWhitelisted,
                         WhitelistedTest,
                         testing::Values(std::make_tuple("NONE", Whitelisted::NONE),
                                         std::make_tuple("SEND_AND_RECEIVE", Whitelisted::SEND_AND_RECEIVE),
                                         std::make_tuple("SEND", Whitelisted::SEND),
                                         std::make_tuple("RECEIVE", Whitelisted::RECEIVE),
                                         std::make_tuple("NO_FEES", Whitelisted::NO_FEES),
                                         std::make_tuple("ADDRESS", Whitelisted::ADDRESS)));
