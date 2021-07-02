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

#ifndef ENJINSDK_FUTUREUTILS_HPP
#define ENJINSDK_FUTUREUTILS_HPP

#include "enjinsdk_export.h"
#include <future>
#include <string>

namespace enjin::sdk::utils {

/// \brief Returns a future that has already completed.
/// \return The future.
ENJINSDK_EXPORT
std::future<void> create_completed_future();

/// \brief Returns a future that throws a runtime error with the given message.
/// \param message The error message.
/// \return The future.
ENJINSDK_EXPORT
std::future<void> create_failed_future(const std::string& message);

}

#endif //ENJINSDK_FUTUREUTILS_HPP
