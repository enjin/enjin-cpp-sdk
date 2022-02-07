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

#include "enjinsdk/internal/Timer.hpp"
#include "gtest/gtest.h"
#include <chrono>
#include <functional>
#include <thread>

using namespace enjin::sdk::utils;

class TimerTest : public testing::Test {
public:
    Timer class_under_test;
};

TEST_F(TimerTest, ScheduleTimerCompletesScheduledActionFlagIsSet) {
    // Arrange
    bool flag = false;
    const std::function<void()> action = [&flag]() {
        flag = true;
    };
    const std::chrono::milliseconds duration(100);

    // Act
    class_under_test.schedule(action, duration);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Assert
    ASSERT_TRUE(flag);
}

TEST_F(TimerTest, ScheduleScheduledTaskIsOverriddenFlagOneIsNotSetAndFlagTwoIsSet) {
    // Arrange
    bool flag1 = false;
    bool flag2 = false;
    const std::function<void()> action1 = [&flag1]() {
        flag1 = true;
    };
    const std::function<void()> action2 = [&flag2]() {
        flag2 = true;
    };
    const std::chrono::milliseconds duration1(500);
    const std::chrono::milliseconds duration2(100);
    class_under_test.schedule(action1, duration1);

    // Act
    class_under_test.schedule(action2, duration2);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Assert
    EXPECT_FALSE(flag1);
    EXPECT_TRUE(flag2);
}

TEST_F(TimerTest, CancelTimerDoesNotCompleteScheduledActionFlagIsNotSet) {
    // Arrange
    bool flag = false;
    class_under_test.schedule([&flag]() {
        flag = true;
    }, std::chrono::milliseconds(10000));

    // Act
    class_under_test.cancel();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Assert
    ASSERT_FALSE(flag);
}

TEST_F(TimerTest, IsEnabledTimerHasNotBeenScheduledReturnsFalse) {
    // Act
    auto actual = class_under_test.is_enabled();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TimerTest, IsEnabledBeforeTimerHasCompletedScheduledActionReturnsTrue) {
    // Arrange
    class_under_test.schedule([]() {}, std::chrono::milliseconds(10000));

    // Act
    auto actual = class_under_test.is_enabled();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TimerTest, IsEnabledAfterTimerHasCompletedScheduledActionReturnsFalse) {
    // Arrange
    class_under_test.schedule([]() {}, std::chrono::milliseconds(500));

    EXPECT_TRUE(class_under_test.is_enabled());

    // Act
    auto actual = class_under_test.is_enabled();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Assert
    ASSERT_TRUE(actual);
}
