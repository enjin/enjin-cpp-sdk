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

#include "MockEventListener.hpp"
#include "MockWebsocketClient.hpp"
#include "PusherEventListener.hpp"
#include <memory>

using namespace enjin::pusher;
using namespace enjin::sdk::events;
using namespace enjin::sdk::models;
using namespace enjin::test::mocks;
using ::testing::An;

class PusherEventListenerTest : public testing::Test {
public:
    std::unique_ptr<PusherEventListener> class_under_test;
    std::unique_ptr<PusherEventService> fake_service;
    std::shared_ptr<MockEventListener> mock_listener;

    static constexpr EventType DEFAULT_EVENT_TYPE = EventType::ProjectCreated;

    static NotificationEvent create_default_notification_event() {
        return NotificationEvent(DEFAULT_EVENT_TYPE, "enjincloud.test.project.1", "{}");
    }

    static PusherEvent create_default_pusher_event() {
        auto event = PusherEvent();
        event.deserialize(
                R"({"channel":"enjincloud.test.project.1","event":"EnjinCloud\\Events\\ProjectCreated","data":"{}"})");
        return event;
    }

protected:
    void SetUp() override {
        fake_service = std::make_unique<PusherEventService>(PusherEventService::builder()
                .ws_client(std::make_unique<MockWebsocketClient>())
                .build());
        class_under_test = std::make_unique<PusherEventListener>(fake_service.get());
        mock_listener = std::make_shared<MockEventListener>();
    }
};

TEST_F(PusherEventListenerTest, OnEventForAllowedEventWithRegisteredListenerDoesNotifyListener) {
    // Arrange - Data
    const NotificationEvent notification_event = create_default_notification_event();
    const PusherEvent pusher_event = create_default_pusher_event();
    fake_service->register_listener_including_types(mock_listener, {DEFAULT_EVENT_TYPE});

    // Arrange - Expectations
    EXPECT_CALL(*mock_listener, notification_received(notification_event))
            .Times(1);

    // Act
    class_under_test->on_event(pusher_event);

    // Verify (done by GTest)
}

TEST_F(PusherEventListenerTest, OnEventForIgnoredEventWithRegisteredListenerDoesNotNotifyListener) {
    // Arrange - Data
    const NotificationEvent notification_event = create_default_notification_event();
    const PusherEvent pusher_event = create_default_pusher_event();
    fake_service->register_listener_excluding_types(mock_listener, {DEFAULT_EVENT_TYPE});

    // Arrange - Expectations
    EXPECT_CALL(*mock_listener, notification_received(notification_event))
            .Times(0);

    // Act
    class_under_test->on_event(pusher_event);

    // Verify (done by GTest)
}

TEST_F(PusherEventListenerTest, OnEventForUnknownEventWithRegisteredListenerDoesNotNotifyListener) {
    // Arrange - Data
    const PusherEvent pusher_event;
    fake_service->register_listener(mock_listener);

    // Arrange - Expectations
    EXPECT_CALL(*mock_listener, notification_received(An<const NotificationEvent&>()))
            .Times(0);

    // Act
    class_under_test->on_event(pusher_event);

    // Verify (done by GTest)
}
