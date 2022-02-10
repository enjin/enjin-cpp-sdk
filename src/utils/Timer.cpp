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

#include <utility>

namespace enjin::sdk::utils {

Timer::Timer() {
    timer_thread = std::thread([this]() {
        std::unique_lock<std::mutex> lock(timer_mutex);

        while (!teardown) {
            if (!duration.has_value()) {
                /* Waits until notified of a state change, then loops again and checks if in the teardown phase or if
                 * duration has been set.
                 */
                timer_cv.wait(lock);
                continue;
            }

            timer_cv.wait_for(lock, duration.value());

            /* Stores action to local variable called outside the locked section to allow any scheduled action to call
             * any of this timer's member-functions.
             */
            std::optional<std::function<void()>> action_opt;
            if (enabled) {
                action_opt = std::move(action);
                reset();
            }
            lock.unlock();

            if (action_opt.has_value()) {
                action_opt.value()();
            }

            lock.lock(); // Reacquires lock to allow safe checking of `teardown` flag
        }
    });
}

Timer::~Timer() {
    std::unique_lock<std::mutex> lock(timer_mutex);
    teardown = true;
    enabled = false;
    timer_cv.notify_one();
    lock.unlock();

    if (timer_thread.joinable()) {
        timer_thread.join();
    }
}

void Timer::schedule(std::function<void()> action, const std::chrono::milliseconds& duration) {
    cancel();

    std::lock_guard<std::mutex> guard(timer_mutex);
    enabled = true;
    Timer::action = std::move(action);
    Timer::duration = duration;
    timer_cv.notify_one();
}

void Timer::cancel() {
    std::lock_guard<std::mutex> guard(timer_mutex);
    reset();
    timer_cv.notify_one();
}

bool Timer::is_enabled() const {
    std::lock_guard<std::mutex> guard(timer_mutex);
    return enabled;
}

void Timer::reset() {
    enabled = false;
    action.reset();
    duration.reset();
}

}
