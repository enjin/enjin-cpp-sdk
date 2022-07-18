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
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>

using testing::MockFunction;
using namespace enjin::sdk::utils;

class TimerTest : public testing::Test {
public:
    Timer class_under_test;
};

TEST_F(TimerTest, ScheduleTimerCompletesScheduledActionFlagIsSet) {
    // Arrange - Data
    const std::chrono::milliseconds duration(100);
    MockFunction<void()> mock_action;

    // Arrange - Expectations
    EXPECT_CALL(mock_action, Call()).Times(1);

    // Act
    class_under_test.schedule(mock_action.AsStdFunction(), duration);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Verify (done by GTest)
}

TEST_F(TimerTest, ScheduleScheduledTaskIsOverriddenFlagOneIsNotSetAndFlagTwoIsSet) {
    // Arrange - Data
    const std::chrono::milliseconds duration1(500);
    const std::chrono::milliseconds duration2(100);
    MockFunction<void()> mock_action1;
    MockFunction<void()> mock_action2;

    // Arrange - Expectations
    EXPECT_CALL(mock_action1, Call()).Times(0);
    EXPECT_CALL(mock_action2, Call()).Times(1);

    // Arrange - Data (continued)
    class_under_test.schedule(mock_action1.AsStdFunction(), duration1);

    // Act
    class_under_test.schedule(mock_action2.AsStdFunction(), duration2);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Verify (done by GTest)
}

TEST_F(TimerTest, CancelTimerDoesNotCompleteScheduledActionFlagIsNotSet) {
    // Arrange - Data
    const std::chrono::milliseconds duration(10000);
    MockFunction<void()> mock_action;

    // Arrange - Expectations
    EXPECT_CALL(mock_action, Call()).Times(0);

    // Arrange - Data (continued)
    class_under_test.schedule(mock_action.AsStdFunction(), duration);

    // Act
    class_under_test.cancel();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Verify (done by GTest)
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
    bool flag = false;
    class_under_test.schedule([&flag]() {
        flag = true;
    }, std::chrono::milliseconds(500));

    // Assumption
    ASSERT_TRUE(class_under_test.is_enabled()) << "Timer was not enabled.";

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Assumption (continued)
    ASSERT_TRUE(flag) << "Timer did not perform scheduled action.";

    // Act
    auto actual = class_under_test.is_enabled();

    // Assert
    ASSERT_FALSE(actual) << "Timer was still enabled.";
}

TEST_F(TimerTest, RescheduleTimerFromWithinScheduledAction) {
    // Arrange - Data
    const std::chrono::milliseconds duration(100);
    MockFunction<void()> mock_action1;
    MockFunction<void()> mock_action2;

    // Arrange - Mocking/Expectations
    EXPECT_CALL(mock_action1, Call()).Times(1).WillOnce([this, duration, &mock_action2]() {
        class_under_test.schedule(mock_action2.AsStdFunction(), duration);
    });
    EXPECT_CALL(mock_action2, Call()).Times(1);

    // Act
    class_under_test.schedule(mock_action1.AsStdFunction(), duration);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Verify (done by GTest)
}
