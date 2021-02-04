#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class EventTypeTest : public testing::TestWithParam<std::tuple<std::string, EventType>> {
};

TEST_P(EventTypeTest, DeserializeEventTypeReturnsExpectedValue) {
    // Arrange
    EventType expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    EventType actual = deserialize_event_type(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(EventTypeTest, SerializeEventTypeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    EventType value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_event_type(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableRequestState,
                         EventTypeTest,
                         testing::Values(std::make_tuple("APP_CREATED", EventType::APP_CREATED),
                                         std::make_tuple("APP_DELETED", EventType::APP_DELETED),
                                         std::make_tuple("APP_LINKED", EventType::APP_LINKED),
                                         std::make_tuple("APP_LOCKED", EventType::APP_LOCKED),
                                         std::make_tuple("APP_UNLINKED", EventType::APP_UNLINKED),
                                         std::make_tuple("APP_UNLOCKED", EventType::APP_UNLOCKED),
                                         std::make_tuple("APP_UPDATED", EventType::APP_UPDATED),
                                         std::make_tuple("BLOCKCHAIN_LOG_PROCESSED",
                                                         EventType::BLOCKCHAIN_LOG_PROCESSED),
                                         std::make_tuple("MESSAGE_PROCESSED", EventType::MESSAGE_PROCESSED),
                                         std::make_tuple("PLAYER_CREATED", EventType::PLAYER_CREATED),
                                         std::make_tuple("PLAYER_DELETED", EventType::PLAYER_DELETED),
                                         std::make_tuple("PLAYER_LINKED", EventType::PLAYER_LINKED),
                                         std::make_tuple("PLAYER_UNLINKED", EventType::PLAYER_UNLINKED),
                                         std::make_tuple("PLAYER_UPDATED", EventType::PLAYER_UPDATED),
                                         std::make_tuple("TOKEN_CREATED", EventType::TOKEN_CREATED),
                                         std::make_tuple("TOKEN_MELTED", EventType::TOKEN_MELTED),
                                         std::make_tuple("TOKEN_MINTED", EventType::TOKEN_MINTED),
                                         std::make_tuple("TOKEN_TRANSFERRED", EventType::TOKEN_TRANSFERRED),
                                         std::make_tuple("TOKEN_UPDATED", EventType::TOKEN_UPDATED),
                                         std::make_tuple("TRADE_COMPLETED", EventType::TRADE_COMPLETED),
                                         std::make_tuple("TRADE_CREATED", EventType::TRADE_CREATED),
                                         std::make_tuple("TRANSACTION_BROADCAST", EventType::TRANSACTION_BROADCAST),
                                         std::make_tuple("TRANSACTION_CANCELED", EventType::TRANSACTION_CANCELED),
                                         std::make_tuple("TRANSACTION_DROPPED", EventType::TRANSACTION_DROPPED),
                                         std::make_tuple("TRANSACTION_EXECUTED", EventType::TRANSACTION_EXECUTED),
                                         std::make_tuple("TRANSACTION_FAILED", EventType::TRANSACTION_FAILED),
                                         std::make_tuple("TRANSACTION_PENDING", EventType::TRANSACTION_PENDING),
                                         std::make_tuple("TRANSACTION_PROCESSING", EventType::TRANSACTION_PROCESSING),
                                         std::make_tuple("TRANSACTION_UPDATED", EventType::TRANSACTION_UPDATED),
                                         std::make_tuple("", EventType::UNKNOWN)));
