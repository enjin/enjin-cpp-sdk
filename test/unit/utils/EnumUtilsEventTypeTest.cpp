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
                         testing::Values(std::make_tuple("PROJECT_CREATED", EventType::ProjectCreated),
                                         std::make_tuple("PROJECT_DELETED", EventType::ProjectDeleted),
                                         std::make_tuple("PROJECT_LINKED", EventType::ProjectLinked),
                                         std::make_tuple("PROJECT_LOCKED", EventType::ProjectLocked),
                                         std::make_tuple("PROJECT_UNLINKED", EventType::ProjectUnlinked),
                                         std::make_tuple("PROJECT_UNLOCKED", EventType::ProjectUnlocked),
                                         std::make_tuple("PROJECT_UPDATED", EventType::ProjectUpdated),
                                         std::make_tuple("BLOCKCHAIN_LOG_PROCESSED",
                                                         EventType::BlockchainLogProcessed),
                                         std::make_tuple("MESSAGE_PROCESSED", EventType::MessageProcessed),
                                         std::make_tuple("PLAYER_CREATED", EventType::PlayerCreated),
                                         std::make_tuple("PLAYER_DELETED", EventType::PlayerDeleted),
                                         std::make_tuple("PLAYER_LINKED", EventType::PlayerLinked),
                                         std::make_tuple("PLAYER_UNLINKED", EventType::PlayerUnlinked),
                                         std::make_tuple("PLAYER_UPDATED", EventType::PlayerUpdated),
                                         std::make_tuple("ASSET_CREATED", EventType::AssetCreated),
                                         std::make_tuple("ASSET_MELTED", EventType::AssetMelted),
                                         std::make_tuple("ASSET_MINTED", EventType::AssetMinted),
                                         std::make_tuple("ASSET_TRANSFERRED", EventType::AssetTransferred),
                                         std::make_tuple("ASSET_UPDATED", EventType::AssetUpdated),
                                         std::make_tuple("TRADE_ASSET_COMPLETED", EventType::TradeAssetCompleted),
                                         std::make_tuple("TRADE_ASSET_CREATED", EventType::TradeAssetCreated),
                                         std::make_tuple("TRANSACTION_BROADCAST", EventType::TransactionBroadcast),
                                         std::make_tuple("TRANSACTION_CANCELED", EventType::TransactionCanceled),
                                         std::make_tuple("TRANSACTION_DROPPED", EventType::TransactionDropped),
                                         std::make_tuple("TRANSACTION_EXECUTED", EventType::TransactionExecuted),
                                         std::make_tuple("TRANSACTION_FAILED", EventType::TransactionFailed),
                                         std::make_tuple("TRANSACTION_PENDING", EventType::TransactionPending),
                                         std::make_tuple("TRANSACTION_PROCESSING", EventType::TransactionProcessing),
                                         std::make_tuple("TRANSACTION_UPDATED", EventType::TransactionUpdated),
                                         std::make_tuple("", EventType::Unknown)));
