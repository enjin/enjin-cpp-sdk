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

#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class RequestTypeTest : public testing::TestWithParam<std::tuple<std::string, RequestType>> {
};

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

INSTANTIATE_TEST_SUITE_P(SerializableRequestType,
                         RequestTypeTest,
                         testing::Values(std::make_tuple("ACCEPT_ASSIGNMENT", RequestType::AcceptAssignment),
                                         std::make_tuple("ASSIGN", RequestType::Assign),
                                         std::make_tuple("APPROVE", RequestType::Approve),
                                         std::make_tuple("CREATE", RequestType::Create),
                                         std::make_tuple("MINT", RequestType::Mint),
                                         std::make_tuple("SEND", RequestType::Send),
                                         std::make_tuple("SEND_ENJ", RequestType::SendEnj),
                                         std::make_tuple("ADVANCED_SEND", RequestType::AdvancedSend),
                                         std::make_tuple("CREATE_TRADE", RequestType::CreateTrade),
                                         std::make_tuple("CANCEL_TRADE", RequestType::CancelTrade),
                                         std::make_tuple("MELT", RequestType::Melt),
                                         std::make_tuple("UPDATE_NAME", RequestType::UpdateName),
                                         std::make_tuple("SET_ITEM_URI", RequestType::SetItemUri),
                                         std::make_tuple("SET_WHITELISTED", RequestType::SetWhitelisted),
                                         std::make_tuple("SET_TRANSFERABLE", RequestType::SetTransferable),
                                         std::make_tuple("SET_MELT_FEE", RequestType::SetMeltFee),
                                         std::make_tuple("DECREASE_MAX_MELT_FEE", RequestType::DecreaseMaxMeltFee),
                                         std::make_tuple("SET_TRANSFER_FEE", RequestType::SetTransferFee),
                                         std::make_tuple("DECREASE_MAX_TRANSFER_FEE",
                                                         RequestType::DecreaseMaxTransferFee),
                                         std::make_tuple("RELEASE_RESERVE", RequestType::ReleaseReserve),
                                         std::make_tuple("ADD_LOG", RequestType::AddLog),
                                         std::make_tuple("SET_APPROVAL_FOR_ALL", RequestType::SetApprovalForAll),
                                         std::make_tuple("MANAGE_UPDATE", RequestType::ManageUpdate),
                                         std::make_tuple("SET_DECIMALS", RequestType::SetDecimals),
                                         std::make_tuple("SET_SYMBOL", RequestType::SetSymbol),
                                         std::make_tuple("MESSAGE", RequestType::Message),
                                         std::make_tuple("", RequestType::Unknown)));
