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
    static constexpr char PlatformJson[] =
            R"({"network":"test","notifications":{"pusher":{"key":"1","options":{"cluster":"mt1","encrypted":true}}}})";

    static constexpr EventType EventTypes[] = {
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

    std::unique_ptr<PusherEventService> class_under_test;

    static Platform create_default_platform() {
        Platform platform;
        platform.deserialize(PlatformJson);
        return platform;
    }

protected:
    void SetUp() override {
        class_under_test = PusherEventService::builder()
                .ws_client(std::make_unique<DummyWebsocketClient>())
                .platform(create_default_platform())
                .build();
    }
};

TEST_F(PusherEventServiceTest, IsRegisteredWhenNotRegisteredReturnsFalse) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    const bool actual = class_under_test->is_registered(*listener);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredNormallyReturnsTrue) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    class_under_test->register_listener(listener);

    // Act
    const bool actual = class_under_test->is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredWithMatcherReturnsTrue) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    const std::function<bool(EventType)> matcher;
    class_under_test->register_listener_with_matcher(listener, matcher);

    // Act
    const bool actual = class_under_test->is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredWithIncludingTypesReturnsTrue) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    const std::vector<EventType> types;
    class_under_test->register_listener_including_types(listener, types);

    // Act
    const bool actual = class_under_test->is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, IsRegisteredWhenRegisteredWithExcludingTypesReturnsTrue) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    const std::vector<EventType> types;
    class_under_test->register_listener_excluding_types(listener, types);

    // Act
    const bool actual = class_under_test->is_registered(*listener);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceTest, RegisterListenerRegistrationHasListener) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    EventListenerRegistration registration = class_under_test->register_listener(listener);

    // Assert
    ASSERT_EQ(listener.get(), &(registration.get_listener()));
}

TEST_F(PusherEventServiceTest, RegisterListenerReturnsRegistrationWithSameListener) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    const EventListenerRegistration expected = class_under_test->register_listener(listener);

    // Act
    const EventListenerRegistration actual = class_under_test->register_listener(listener);

    // Assert
    EXPECT_EQ(&expected.get_listener(), &actual.get_listener());
}

TEST_F(PusherEventServiceTest, RegisterListenerWithMatcherRegistrationHasMatcher) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    const std::function<bool(EventType)> matcher = [](EventType type) {
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
    const EventListenerRegistration registration = class_under_test->register_listener_with_matcher(listener, matcher);

    // Assert
    for (const EventType type: EventTypes) {
        const bool expected = matcher(type);
        const bool actual = registration.get_matcher()(type);

        EXPECT_EQ(expected, actual);
    }
}

TEST_F(PusherEventServiceTest, RegisterListenerIncludingTypesRegistrationMatcherIncludesTypes) {
    // Arrange
    const std::vector<EventType> types = {
            EventType::PlayerCreated,
            EventType::PlayerUpdated,
            EventType::AssetTransferred
    };
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    const EventListenerRegistration registration = class_under_test->register_listener_including_types(listener, types);

    // Assert
    for (const EventType type: EventTypes) {
        const bool expected = std::find(types.begin(), types.end(), type) != types.end();
        const bool actual = registration.get_matcher()(type);

        EXPECT_EQ(expected, actual);
    }
}

TEST_F(PusherEventServiceTest, RegisterListenerExcludingTypesRegistrationMatcherExcludesTypes) {
    // Arrange
    const std::vector<EventType> types = {
            EventType::PlayerCreated,
            EventType::PlayerUpdated,
            EventType::AssetTransferred
    };
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Act
    const EventListenerRegistration registration = class_under_test->register_listener_excluding_types(listener, types);

    // Assert
    for (const EventType type: EventTypes) {
        const bool expected = std::find(types.begin(), types.end(), type) == types.end();
        const bool actual = registration.get_matcher()(type);

        EXPECT_EQ(expected, actual);
    }
}

TEST_F(PusherEventServiceTest, UnregisterListenerListenerIsUnregestered) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();
    const EventListenerRegistration registration = class_under_test->register_listener(listener);

    // Assumptions
    ASSERT_EQ(listener.get(), &(registration.get_listener())) << "Assume listener is registered";

    // Act
    class_under_test->unregister_listener(*listener);

    // Assert
    ASSERT_FALSE(class_under_test->is_registered(*listener)) << "Listener was not unregistered";
}

TEST_F(PusherEventServiceTest, UnregisterListenerListenerWasNotUnregesteredDoesNotThrowException) {
    // Arrange
    const std::shared_ptr<MockEventListener> listener = std::make_shared<MockEventListener>();

    // Assert
    ASSERT_NO_THROW(class_under_test->unregister_listener(*listener));
}
