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

#include "VerificationTestSuite.hpp"

#include "gtest/gtest.h"
#include <chrono>

namespace enjin::test::suites {

void VerificationTestSuite::set_expected_call_count(int count) {
    std::lock_guard<std::mutex> guard(count_mutex);
    expected_count = count;
}

void VerificationTestSuite::increment_call_counter() {
    std::lock_guard<std::mutex> guard(count_mutex);
    call_counter++;
    cv.notify_all();
}

void VerificationTestSuite::verify_call_count(int seconds) {
    std::unique_lock<std::mutex> lock(count_mutex);

    // Waits and gives the calls an opportunity to be made if asynchronous
    cv.wait_for(lock, std::chrono::seconds(seconds), [this]() {
        return expected_count == call_counter;
    });

    EXPECT_EQ(expected_count, call_counter);
}

}
