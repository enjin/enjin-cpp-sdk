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

#include "enjinsdk/EventListenerRegistration.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace enjin::sdk::events;
using namespace enjin::sdk::models;

class EventListenerRegistrationTest : public testing::Test {
public:
    inline static const std::vector<EventType> types = {
            EventType::Unknown,
            EventType::ProjectCreated,
            EventType::ProjectDeleted,
            EventType::ProjectLinked,
            EventType::ProjectLocked,
            EventType::ProjectUnlinked,
            EventType::ProjectUnlocked,
            EventType::ProjectUpdated,
            EventType::BlockchainLogProcessed,
            EventType::MessageProcessed,
            EventType::PlayerCreated,
            EventType::PlayerDeleted,
            EventType::PlayerLinked,
            EventType::PlayerUnlinked,
            EventType::PlayerUpdated,
            EventType::AssetCreated,
            EventType::AssetMelted,
            EventType::AssetMinted,
            EventType::AssetTransferred,
            EventType::AssetUpdated,
            EventType::TradeAssetCompleted,
            EventType::TradeAssetCreated,
            EventType::TransactionBroadcast,
            EventType::TransactionCanceled,
            EventType::TransactionDropped,
            EventType::TransactionExecuted,
            EventType::TransactionFailed,
            EventType::TransactionPending,
            EventType::TransactionProcessing,
            EventType::TransactionUpdated,
    };
};

TEST_F(EventListenerRegistrationTest, AllowAllMatcherAllowsAllEventTypes) {
    // Assert
    for (auto t : types) {
        EXPECT_TRUE(EventListenerRegistration::ALLOW_ALL_MATCHER(t));
    }
}
