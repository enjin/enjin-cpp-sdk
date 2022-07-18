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

#ifndef ENJINSDK_ILOGGER_HPP
#define ENJINSDK_ILOGGER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/LogLevel.hpp"
#include <string>

namespace enjin::sdk::utils {

/// \brief Logger interface to be implemented for use by the SDK.
class ENJINSDK_EXPORT ILogger {
public:
    /// \brief Default destructor.
    virtual ~ILogger() = default;

    /// \brief Logs the message at the given logging level.
    /// \param level The logging level.
    /// \param message The message.
    virtual void log(LogLevel level, const std::string& message) = 0;

    /// \brief Formats and logs the message and exception at the given logging level.
    /// \param level The logging level.
    /// \param message The message.
    /// \param e The exception.
    virtual void log(LogLevel level, const std::string& message, const std::exception& e) = 0;

    /// \brief Determines if the given logging level is enabled for this logger.
    /// \param level The logging level.
    /// \return Whether this logger is enabled for the given logging level.
    [[nodiscard]] virtual bool is_loggable(LogLevel level) const = 0;
};

}

#endif //ENJINSDK_ILOGGER_HPP
