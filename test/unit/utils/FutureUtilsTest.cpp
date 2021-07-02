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
#include "FutureUtils.hpp"
#include <chrono>
#include <future>
#include <string>

using namespace enjin::sdk::utils;

class FutureUtilsTest : public testing::Test {
};

TEST_F(FutureUtilsTest, CreateCompletedFutureFutureCompletesImmediately) {
    // Arrange
    const std::future_status expected_status = std::future_status::ready;
    const std::chrono::milliseconds timeout = std::chrono::milliseconds(0);

    // Act
    std::future<void> future = create_completed_future();

    // Assert
    EXPECT_TRUE(future.valid());
    EXPECT_EQ(expected_status, future.wait_for(timeout));
    EXPECT_NO_THROW(future.get());
}

TEST_F(FutureUtilsTest, CreateFailedFutureReturnedFutureThrowsException) {
    // Arrange
    const std::string message("Test exception");

    // Act
    std::future<void> future = create_failed_future(message);

    // Assert
    EXPECT_TRUE(future.valid());
    EXPECT_ANY_THROW(future.get());
}
