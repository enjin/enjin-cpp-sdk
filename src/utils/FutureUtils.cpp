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

#include "FutureUtils.hpp"

#include <stdexcept>

namespace enjin::sdk::utils {

std::future<void> create_completed_future() {
    auto fut = std::async([]() {});
    fut.wait();
    return fut;
}

std::future<void> create_failed_future(const std::string& message) {
    return std::async([message]() {
        throw std::runtime_error(message);
    });
}

}
