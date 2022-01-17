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

#include <condition_variable>
#include <mutex>

namespace enjin::test::suites {

/// \brief Test suite to assist in setting expectations and verifying asynchronous operations.
class VerificationTestSuite {
public:
    /// \brief Default constructor.
    VerificationTestSuite() = default;

    /// \brief Default destructor.
    ~VerificationTestSuite() = default;

    /// \brief Sets the expected number of times a operation is expected to call the increment_call_counter() member
    /// function.
    /// \param count The expected call count.
    void set_expected_call_count(int count);

    /// \brief Increments the call counter.
    void increment_call_counter();

    /// \brief Verifies that the actual call count is equal to the expected call count.
    /// \param seconds The number of seconds before this verification checks times out.
    void verify_call_count(int seconds = 5);

private:
    int call_counter = 0;
    int expected_count = 0;
    std::condition_variable cv;

    // Mutexes
    mutable std::mutex count_mutex;
};

}

#endif //ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP
