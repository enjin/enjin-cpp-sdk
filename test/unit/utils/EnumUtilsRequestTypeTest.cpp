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
