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

#ifndef ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP
#define ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP

#include <atomic>
#include <chrono>
#include <mutex>

namespace enjin::test::suites {

class VerificationTestSuite {
public:
    VerificationTestSuite();

    void set_expected_call_count(int count);

    void increment_call_counter();

    void verify_call_count(int time = 0) const;

private:
    std::atomic_int call_counter;
    int expected_count;
};

}

#endif //ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP
