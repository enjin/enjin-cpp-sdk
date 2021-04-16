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

class EventListenerRegistrationTest : public testing::Test {
public:
    inline static const std::vector<enjin::sdk::models::EventType> types = {
            enjin::sdk::models::EventType::UNKNOWN,
            enjin::sdk::models::EventType::PROJECT_CREATED,
            enjin::sdk::models::EventType::PROJECT_DELETED,
            enjin::sdk::models::EventType::PROJECT_LINKED,
            enjin::sdk::models::EventType::PROJECT_LOCKED,
            enjin::sdk::models::EventType::PROJECT_UNLINKED,
            enjin::sdk::models::EventType::PROJECT_UNLOCKED,
            enjin::sdk::models::EventType::PROJECT_UPDATED,
            enjin::sdk::models::EventType::BLOCKCHAIN_LOG_PROCESSED,
            enjin::sdk::models::EventType::MESSAGE_PROCESSED,
            enjin::sdk::models::EventType::PLAYER_CREATED,
            enjin::sdk::models::EventType::PLAYER_DELETED,
            enjin::sdk::models::EventType::PLAYER_LINKED,
            enjin::sdk::models::EventType::PLAYER_UNLINKED,
            enjin::sdk::models::EventType::PLAYER_UPDATED,
            enjin::sdk::models::EventType::ASSET_CREATED,
            enjin::sdk::models::EventType::ASSET_MELTED,
            enjin::sdk::models::EventType::ASSET_MINTED,
            enjin::sdk::models::EventType::ASSET_TRANSFERRED,
            enjin::sdk::models::EventType::ASSET_UPDATED,
            enjin::sdk::models::EventType::TRADE_COMPLETED,
            enjin::sdk::models::EventType::TRADE_CREATED,
            enjin::sdk::models::EventType::TRANSACTION_BROADCAST,
            enjin::sdk::models::EventType::TRANSACTION_CANCELED,
            enjin::sdk::models::EventType::TRANSACTION_DROPPED,
            enjin::sdk::models::EventType::TRANSACTION_EXECUTED,
            enjin::sdk::models::EventType::TRANSACTION_FAILED,
            enjin::sdk::models::EventType::TRANSACTION_PENDING,
            enjin::sdk::models::EventType::TRANSACTION_PROCESSING,
            enjin::sdk::models::EventType::TRANSACTION_UPDATED,
    };
};

TEST_F(EventListenerRegistrationTest, AllowAllMatcherAllowsAllEventTypes) {
    // Assert
    for (auto t : types) {
        EXPECT_TRUE(EventListenerRegistration::ALLOW_ALL_MATCHER(t));
    }
}
