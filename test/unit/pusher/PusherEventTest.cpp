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
#include "JsonTestSuite.hpp"
#include "PusherEvent.hpp"
#include <string>

using namespace enjin::pusher;
using namespace enjin::test::suites;

class PusherEventTest : public JsonTestSuite,
                        public testing::Test {
public:
    PusherEvent class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"user_id":"1","channel":"1","event":"1","data":"1"})";

    static PusherEvent create_default_pusher_event() {
        PusherEvent event;
        event.deserialize(POPULATED_JSON_OBJECT);
        return event;
    }
};

TEST_F(PusherEventTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_user_id().has_value());
    EXPECT_FALSE(class_under_test.get_channel_name().has_value());
    EXPECT_FALSE(class_under_test.get_event_name().has_value());
    EXPECT_FALSE(class_under_test.get_data().has_value());
}

TEST_F(PusherEventTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_user_id().has_value());
    EXPECT_FALSE(class_under_test.get_channel_name().has_value());
    EXPECT_FALSE(class_under_test.get_event_name().has_value());
    EXPECT_FALSE(class_under_test.get_data().has_value());
}

TEST_F(PusherEventTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_user_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_channel_name().value());
    EXPECT_EQ(expected_string, class_under_test.get_event_name().value());
    EXPECT_EQ(expected_string, class_under_test.get_data().value());
}

TEST_F(PusherEventTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PusherEvent lhs;
    PusherEvent rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PusherEvent lhs = create_default_pusher_event();
    PusherEvent rhs = create_default_pusher_event();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PusherEvent lhs = create_default_pusher_event();
    PusherEvent rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PusherEventTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PusherEvent lhs;
    PusherEvent rhs = create_default_pusher_event();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
