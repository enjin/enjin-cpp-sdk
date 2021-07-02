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

#ifndef ENJINSDK_TIMEOUTEXCEPTION_HPP
#define ENJINSDK_TIMEOUTEXCEPTION_HPP

#include "enjinsdk_export.h"
#include <stdexcept>
#include <string>

namespace enjin::sdk {

/// \brief Exception indicating that an operation has reached its timeout period.
class ENJINSDK_EXPORT TimeoutException : public std::runtime_error {
public:
    TimeoutException() = delete;

    /// \brief Constructs the exception with the given message.
    /// \param message The exception message.
    explicit TimeoutException(const std::string& message);

    ~TimeoutException() noexcept override = default;
};

}

#endif //ENJINSDK_TIMEOUTEXCEPTION_HPP
