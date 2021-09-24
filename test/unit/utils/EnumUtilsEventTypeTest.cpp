/* Copyright 2021 Enjin Pte Ltd.
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

INSTANTIATE_TEST_SUITE_P(SerializableEventType,
                         EventTypeTest,
                         testing::Values(std::make_tuple("PROJECT_CREATED", EventType::PROJECT_CREATED),
                                         std::make_tuple("PROJECT_DELETED", EventType::PROJECT_DELETED),
                                         std::make_tuple("PROJECT_LINKED", EventType::PROJECT_LINKED),
                                         std::make_tuple("PROJECT_LOCKED", EventType::PROJECT_LOCKED),
                                         std::make_tuple("PROJECT_UNLINKED", EventType::PROJECT_UNLINKED),
                                         std::make_tuple("PROJECT_UNLOCKED", EventType::PROJECT_UNLOCKED),
                                         std::make_tuple("PROJECT_UPDATED", EventType::PROJECT_UPDATED),
                                         std::make_tuple("BLOCKCHAIN_LOG_PROCESSED",
                                                         EventType::BLOCKCHAIN_LOG_PROCESSED),
                                         std::make_tuple("MESSAGE_PROCESSED", EventType::MESSAGE_PROCESSED),
                                         std::make_tuple("PLAYER_CREATED", EventType::PLAYER_CREATED),
                                         std::make_tuple("PLAYER_DELETED", EventType::PLAYER_DELETED),
                                         std::make_tuple("PLAYER_LINKED", EventType::PLAYER_LINKED),
                                         std::make_tuple("PLAYER_UNLINKED", EventType::PLAYER_UNLINKED),
                                         std::make_tuple("PLAYER_UPDATED", EventType::PLAYER_UPDATED),
                                         std::make_tuple("ASSET_CREATED", EventType::ASSET_CREATED),
                                         std::make_tuple("ASSET_MELTED", EventType::ASSET_MELTED),
                                         std::make_tuple("ASSET_MINTED", EventType::ASSET_MINTED),
                                         std::make_tuple("ASSET_TRANSFERRED", EventType::ASSET_TRANSFERRED),
                                         std::make_tuple("ASSET_UPDATED", EventType::ASSET_UPDATED),
                                         std::make_tuple("TRADE_ASSET_COMPLETED", EventType::TRADE_ASSET_COMPLETED),
                                         std::make_tuple("TRADE_ASSET_CREATED", EventType::TRADE_ASSET_CREATED),
                                         std::make_tuple("TRANSACTION_BROADCAST", EventType::TRANSACTION_BROADCAST),
                                         std::make_tuple("TRANSACTION_CANCELED", EventType::TRANSACTION_CANCELED),
                                         std::make_tuple("TRANSACTION_DROPPED", EventType::TRANSACTION_DROPPED),
                                         std::make_tuple("TRANSACTION_EXECUTED", EventType::TRANSACTION_EXECUTED),
                                         std::make_tuple("TRANSACTION_FAILED", EventType::TRANSACTION_FAILED),
                                         std::make_tuple("TRANSACTION_PENDING", EventType::TRANSACTION_PENDING),
                                         std::make_tuple("TRANSACTION_PROCESSING", EventType::TRANSACTION_PROCESSING),
                                         std::make_tuple("TRANSACTION_UPDATED", EventType::TRANSACTION_UPDATED),
                                         std::make_tuple("", EventType::UNKNOWN)));
