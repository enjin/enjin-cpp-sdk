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

#ifndef ENJINSDK_TIMER_HPP
#define ENJINSDK_TIMER_HPP

#include "enjinsdk_export.h"

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <optional>
#include <thread>

namespace enjin::sdk::utils {

/// \brief Timer class for scheduling a single action to run once after a given time.
class ENJINSDK_EXPORT Timer {
public:
    /// \brief Constructs an instance of this class.
    Timer();

    /// \brief Deconstructs this instance.
    ~Timer();

    /// \brief Schedules an action to run after the given time duration passes.
    /// \param action The action.
    /// \param duration The wait duration.
    void schedule(std::function<void()> action, const std::chrono::milliseconds& duration);

    /// \brief Cancels the current scheduled action.
    void cancel();

    /// \brief Determines is this timer is enabled.
    /// \return Whether this timer is enabled.
    [[nodiscard]] bool is_enabled() const;

private:
    bool enabled = false;
    std::optional<std::function<void()>> action;
    std::optional<std::chrono::milliseconds> duration;

    bool teardown = false;
    std::condition_variable timer_cv;
    std::thread timer_thread;

    // Mutexes
    mutable std::mutex timer_mutex;

    /// \brief Resets necessary fields used between different schedules of the timer.
    /// \remarks This member-function ought to only be called when the current thread has acquired `timer_mutex`.
    void reset();
};

}

#endif //ENJINSDK_TIMER_HPP
