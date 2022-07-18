/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "enjinsdk/EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TransactionTypeTest : public testing::TestWithParam<std::tuple<std::string, TransactionType>> {
};

TEST_P(TransactionTypeTest, DeserializeTransactionTypeReturnsExpectedValue) {
    // Arrange
    TransactionType expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    TransactionType actual = EnumUtils::deserialize_transaction_type(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TransactionTypeTest, SerializeTransactionTypeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TransactionType value = std::get<1>(GetParam());

    // Act
    std::string actual = EnumUtils::serialize_transaction_type(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableTransactionType,
                         TransactionTypeTest,
                         testing::Values(std::make_tuple("ACCEPT_ASSIGNMENT", TransactionType::AcceptAssignment),
                                         std::make_tuple("ASSIGN", TransactionType::Assign),
                                         std::make_tuple("APPROVE", TransactionType::Approve),
                                         std::make_tuple("CREATE", TransactionType::Create),
                                         std::make_tuple("MINT", TransactionType::Mint),
                                         std::make_tuple("SEND", TransactionType::Send),
                                         std::make_tuple("SEND_ENJ", TransactionType::SendEnj),
                                         std::make_tuple("ADVANCED_SEND", TransactionType::AdvancedSend),
                                         std::make_tuple("CREATE_TRADE", TransactionType::CreateTrade),
                                         std::make_tuple("CANCEL_TRADE", TransactionType::CancelTrade),
                                         std::make_tuple("MELT", TransactionType::Melt),
                                         std::make_tuple("UPDATE_NAME", TransactionType::UpdateName),
                                         std::make_tuple("SET_ITEM_URI", TransactionType::SetItemUri),
                                         std::make_tuple("SET_WHITELISTED", TransactionType::SetWhitelisted),
                                         std::make_tuple("SET_TRANSFERABLE", TransactionType::SetTransferable),
                                         std::make_tuple("SET_MELT_FEE", TransactionType::SetMeltFee),
                                         std::make_tuple("DECREASE_MAX_MELT_FEE", TransactionType::DecreaseMaxMeltFee),
                                         std::make_tuple("SET_TRANSFER_FEE", TransactionType::SetTransferFee),
                                         std::make_tuple("DECREASE_MAX_TRANSFER_FEE",
                                                         TransactionType::DecreaseMaxTransferFee),
                                         std::make_tuple("RELEASE_RESERVE", TransactionType::ReleaseReserve),
                                         std::make_tuple("ADD_LOG", TransactionType::AddLog),
                                         std::make_tuple("SET_APPROVAL_FOR_ALL", TransactionType::SetApprovalForAll),
                                         std::make_tuple("MANAGE_UPDATE", TransactionType::ManageUpdate),
                                         std::make_tuple("SET_DECIMALS", TransactionType::SetDecimals),
                                         std::make_tuple("SET_SYMBOL", TransactionType::SetSymbol),
                                         std::make_tuple("MESSAGE", TransactionType::Message),
                                         std::make_tuple("", TransactionType::Unknown)));
