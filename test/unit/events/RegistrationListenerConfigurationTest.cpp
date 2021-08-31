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

#include "gtest/gtest.h"
#include "MockEventListener.hpp"
#include "enjinsdk/EventListenerRegistration.hpp"
#include <algorithm>
#include <functional>
#include <vector>

using namespace enjin::sdk::events;
using namespace enjin::sdk::models;
using namespace enjin::test::mocks;

class RegistrationListenerConfigurationTest : public testing::Test {
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
            EventType::TRADE_COMPLETED,
            EventType::TRADE_CREATED,
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

TEST_F(RegistrationListenerConfigurationTest, RegistrationHasConfiguredListenerWhenCreated) {
    // Arrange
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    auto registration = configuration.create();

    // Assert
    ASSERT_EQ(mock_listener.get(), &(registration.get_listener()));
}

TEST_F(RegistrationListenerConfigurationTest, NoGivenMatcherRegistrationIsCreatedWithAllowAllMatcher) {
    // Arrange
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    auto registration = configuration.create();

    // Assert
    for (auto t : types) {
        EXPECT_TRUE(registration.get_matcher()(t));
    }
}

TEST_F(RegistrationListenerConfigurationTest, WithMatcherRegistrationIsCreatedWithCorrectMatcher) {
    // Arrange
    const std::function<bool(EventType)> matcher = [](EventType type) {
        return false;
    };
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    auto registration = configuration.with_matcher(matcher)
                                     .create();

    // Assert
    for (auto t : types) {
        EXPECT_FALSE(registration.get_matcher()(t));
    }
}

TEST_F(RegistrationListenerConfigurationTest, WithAllowedEventsRegistrationIsCreatedWithCorrectMatcher) {
    // Arrange
    const std::vector<EventType> allowed_events = {
            EventType::PLAYER_LINKED,
            EventType::PLAYER_UNLINKED,
            EventType::PLAYER_UPDATED,
            EventType::ASSET_MELTED,
            EventType::ASSET_MINTED,
            EventType::ASSET_TRANSFERRED,
            EventType::ASSET_UPDATED,
    };
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    auto registration = configuration.with_allowed_events(allowed_events)
                                     .create();

    // Assert
    for (auto t : types) {
        if (std::find(allowed_events.begin(), allowed_events.end(), t) != allowed_events.end()) {
            EXPECT_TRUE(registration.get_matcher()(t));
        } else {
            EXPECT_FALSE(registration.get_matcher()(t));
        }
    }
}

TEST_F(RegistrationListenerConfigurationTest, WithIgnoredEventsRegistrationIsCreatedWithCorrectMatcher) {
    // Arrange
    const std::vector<EventType> ignored_events = {
            EventType::PLAYER_LINKED,
            EventType::PLAYER_UNLINKED,
            EventType::PLAYER_UPDATED,
            EventType::ASSET_MELTED,
            EventType::ASSET_MINTED,
            EventType::ASSET_TRANSFERRED,
            EventType::ASSET_UPDATED,
    };
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    auto registration = configuration.with_ignored_events(ignored_events)
                                     .create();

    // Assert
    for (auto t : types) {
        if (std::find(ignored_events.begin(), ignored_events.end(), t) == ignored_events.end()) {
            EXPECT_TRUE(registration.get_matcher()(t));
        } else {
            EXPECT_FALSE(registration.get_matcher()(t));
        }
    }
}
