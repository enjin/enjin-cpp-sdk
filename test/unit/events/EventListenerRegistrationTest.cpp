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

#include "enjinsdk/EventListenerRegistration.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace enjin::sdk::events;
using namespace enjin::sdk::models;

class EventListenerRegistrationTest : public testing::Test {
public:
    inline static const std::vector<EventType> types = {
            EventType::UNKNOWN,
            EventType::PROJECT_CREATED,
            EventType::PROJECT_DELETED,
            EventType::PROJECT_LINKED,
            EventType::PROJECT_LOCKED,
            EventType::PROJECT_UNLINKED,
            EventType::PROJECT_UNLOCKED,
            EventType::PROJECT_UPDATED,
            EventType::BLOCKCHAIN_LOG_PROCESSED,
            EventType::MESSAGE_PROCESSED,
            EventType::PLAYER_CREATED,
            EventType::PLAYER_DELETED,
            EventType::PLAYER_LINKED,
            EventType::PLAYER_UNLINKED,
            EventType::PLAYER_UPDATED,
            EventType::ASSET_CREATED,
            EventType::ASSET_MELTED,
            EventType::ASSET_MINTED,
            EventType::ASSET_TRANSFERRED,
            EventType::ASSET_UPDATED,
            EventType::TRADE_ASSET_COMPLETED,
            EventType::TRADE_ASSET_CREATED,
            EventType::TRANSACTION_BROADCAST,
            EventType::TRANSACTION_CANCELED,
            EventType::TRANSACTION_DROPPED,
            EventType::TRANSACTION_EXECUTED,
            EventType::TRANSACTION_FAILED,
            EventType::TRANSACTION_PENDING,
            EventType::TRANSACTION_PROCESSING,
            EventType::TRANSACTION_UPDATED,
    };
};

TEST_F(EventListenerRegistrationTest, AllowAllMatcherAllowsAllEventTypes) {
    // Assert
    for (auto t : types) {
        EXPECT_TRUE(EventListenerRegistration::ALLOW_ALL_MATCHER(t));
    }
}
