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

#include "gtest/gtest.h"
#include "MockEventListener.hpp"
#include "MockWebsocketClient.hpp"
#include "enjinsdk/PusherEventService.hpp"
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

using namespace enjin::sdk::events;
using namespace enjin::sdk::models;
using namespace enjin::test::mocks;

class PusherEventServiceTest : public testing::Test {
public:
    static constexpr char PLATFORM_JSON[] =
            R"({"network":"test","notifications":{"pusher":{"key":"1","options":{"cluster":"mt1","encrypted":true}}}})";

    static constexpr EventType EVENT_TYPES[] = {
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

    static Platform create_default_platform() {
        Platform platform;
        platform.deserialize(PLATFORM_JSON);
        return platform;
    }

    static PusherEventService create_default_event_service() {
        return PusherEventService::builder()
                .ws_client(std::make_unique<DummyWebsocketClient>())
                .platform(create_default_platform())
                .build();
    }
};

TEST_F(PusherEventServiceTest, IsRegisteredWhenNotRegisteredReturnsFalse) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    bool actual = service.is_registered(*listener);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredNormallyReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    service.register_listener(listener);

    // Act
    bool actual = service.is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredWithMatcherReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    std::function<bool(EventType)> matcher;
    service.register_listener_with_matcher(listener, matcher);

    // Act
    bool actual = service.is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredWithIncludingTypesReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    std::vector<EventType> types;
    service.register_listener_including_types(listener, types);

    // Act
    bool actual = service.is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredWithExcludingTypesReturnsTrue) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    std::vector<EventType> types;
    service.register_listener_excluding_types(listener, types);

    // Act
    bool actual = service.is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, RegisterListenerRegistrationHasListener) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    auto registration = service.register_listener(listener);

    // Assert
    ASSERT_EQ(listener.get(), &(registration.get_listener()));
}

TEST_F(PusherEventServiceTest, RegisterListenerReturnsRegistrationWithSameListener) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    auto expected = service.register_listener(listener);

    // Act
    auto actual = service.register_listener(listener);

    // Assert
    EXPECT_EQ(&expected.get_listener(), &actual.get_listener());
}

TEST_F(PusherEventServiceTest, RegisterListenerWithMatcherRegistrationHasMatcher) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    std::function<bool(EventType)> matcher = [](EventType type) {
        switch (type) {
            case EventType::PlayerCreated:
            case EventType::PlayerUpdated:
            case EventType::AssetTransferred:
                return true;
            default:
                return false;
        }
    };

    // Act
    auto registration = service.register_listener_with_matcher(listener, matcher);

    // Assert
    for (EventType type: EVENT_TYPES) {
        bool expected = matcher(type);
        bool actual = registration.get_matcher()(type);
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(PusherEventServiceTest, RegisterListenerIncludingTypesRegistrationMatcherIncludesTypes) {
    // Arrange
    auto service = create_default_event_service();
    std::vector<EventType> types = {
            EventType::PlayerCreated,
            EventType::PlayerUpdated,
            EventType::AssetTransferred
    };
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    auto registration = service.register_listener_including_types(listener, types);

    // Assert
    for (EventType type: EVENT_TYPES) {
        bool expected = std::find(types.begin(), types.end(), type) != types.end();
        bool actual = registration.get_matcher()(type);
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(PusherEventServiceTest, RegisterListenerExcludingTypesRegistrationMatcherExcludesTypes) {
    // Arrange
    auto service = create_default_event_service();
    std::vector<EventType> types = {
            EventType::PlayerCreated,
            EventType::PlayerUpdated,
            EventType::AssetTransferred
    };
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    auto registration = service.register_listener_excluding_types(listener, types);

    // Assert
    for (EventType type: EVENT_TYPES) {
        bool expected = std::find(types.begin(), types.end(), type) == types.end();
        bool actual = registration.get_matcher()(type);
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(PusherEventServiceTest, UnregisterListenerListenerIsUnregestered) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    auto registration = service.register_listener(listener);

    EXPECT_EQ(listener.get(), &(registration.get_listener()));

    // Act
    service.unregister_listener(*listener);

    // Assert
    ASSERT_FALSE(service.is_registered(*listener));
}

TEST_F(PusherEventServiceTest, UnregisterListenerListenerWasNotUnregesteredDoesNotThrowException) {
    // Arrange
    auto service = create_default_event_service();
    std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Assert
    ASSERT_NO_THROW(service.unregister_listener(*listener));
}
