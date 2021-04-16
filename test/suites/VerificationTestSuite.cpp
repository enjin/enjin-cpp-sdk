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

#include "VerificationTestSuite.hpp"

#include "gtest/gtest.h"
#include <condition_variable>

namespace enjin::test::suites {

VerificationTestSuite::VerificationTestSuite() : call_counter(0), expected_count(0) {
}

void VerificationTestSuite::set_expected_call_count(int count) {
    expected_count = count;
}

void VerificationTestSuite::increment_call_counter() {
    call_counter++;
}

void VerificationTestSuite::verify_call_count(int time) const {
    // Waits and gives the calls an opportunity to be made if asynchronous
    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    std::condition_variable condition_variable;
    condition_variable.wait_for(lock, std::chrono::seconds(time), [this]() {
        return expected_count == call_counter;
    });

    EXPECT_EQ(expected_count, call_counter);
}

}
