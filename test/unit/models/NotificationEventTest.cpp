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

#include "enjinsdk/models/NotificationEvent.hpp"
#include "gtest/gtest.h"

using namespace enjin::sdk::models;

class NotificationEventTest : public testing::Test {
};

TEST_F(NotificationEventTest, EqualityBothSidesAreSameDefReturnsTrue) {
    // Arrange
    NotificationEvent lhs = NotificationEvent(EventType::ProjectCreated, "project", "xyz");
    NotificationEvent rhs = NotificationEvent(EventType::ProjectCreated, "project", "xyz");

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(NotificationEventTest, EqualityBothSidesAreNotSameDefReturnsFalse) {
    // Arrange
    NotificationEvent lhs = NotificationEvent(EventType::ProjectCreated, "project", "xyz");
    NotificationEvent rhs = NotificationEvent(EventType::ProjectDeleted, "player", "abc");

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
