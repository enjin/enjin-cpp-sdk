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

#ifndef ENJINCPPSDK_PUSHEREXCEPTION_HPP
#define ENJINCPPSDK_PUSHEREXCEPTION_HPP

#include "enjinsdk_export.h"
#include <stdexcept>
#include <string>

namespace enjin::pusher {

/// \brief Exception class for Pusher events.
class ENJINSDK_EXPORT PusherException : public std::runtime_error {
public:
    /// \brief Constructs the exception with a message and error code.
    /// \param message The message.
    /// \param error_code The error code.
    PusherException(const std::string& message, int error_code);

    ~PusherException() noexcept override = default;

    /// \brief Returns the error exception code.
    /// \return The error code.
    [[nodiscard]] int get_error_code() const;

private:
    int error_code;
};

}

#endif //ENJINCPPSDK_PUSHEREXCEPTION_HPP
