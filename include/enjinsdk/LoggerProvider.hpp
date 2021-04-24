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

#ifndef ENJINSDK_LOGGERPROVIDER_HPP
#define ENJINSDK_LOGGERPROVIDER_HPP

#include "enjinsdk/ILogger.hpp"
#include "enjinsdk_export.h"
#include <memory>
#include <string>

namespace enjin::sdk::utils {

/// \brief Provider class for an instance of ILogger.
class ENJINSDK_EXPORT LoggerProvider {
public:
    LoggerProvider() = delete;

    /// \brief Constructs a provider with the given logger and logging levels.
    /// \param logger The logger.
    /// \param default_level The default logging level.
    /// \param debug_level The debug logging level.
    explicit LoggerProvider(std::shared_ptr<ILogger> logger,
                            LogLevel default_level = LogLevel::INFO,
                            LogLevel debug_level = LogLevel::DEBUG);

    /// \brief Default destructor.
    ~LoggerProvider() = default;

    /// \brief Logs the message at the default logging level.
    /// \param message The message.
    void log(const std::string& message);

    /// \brief Logs the message at the debug logging level.
    /// \param message The message.
    void debug(const std::string& message);

    /// \brief Logs the message at the given logging level.
    /// \param level The logging level.
    /// \param message The message.
    void log(LogLevel level, const std::string& message);

    /// \brief Formats and logs the given message and exception at the default logging level.
    /// \param message The message.
    /// \param e The exception.
    void log(const std::string& message, const std::exception& e);

    /// \brief Formats and logs the given message and exception at the debug logging level.
    /// \param message The message.
    /// \param e The exception.
    void debug(const std::string& message, const std::exception& e);

    /// \brief Formats and logs the given message and exception at the given logging level.
    /// \param level The logging level.
    /// \param message The message.
    /// \param e The exception.
    void log(LogLevel level, const std::string& message, const std::exception& e);

    /// \brief Returns the logger contained by this provider.
    /// \return The logger.
    [[nodiscard]] const std::shared_ptr<ILogger>& get_logger() const;

    /// \brief Returns the default logging level used by this provider.
    /// \return The logging level.
    [[nodiscard]] LogLevel get_default_level() const;

    /// \brief Returns the debug logging level used by this provider.
    /// \return The logging level.
    [[nodiscard]] LogLevel get_debug_level() const;

private:
    std::shared_ptr<ILogger> logger;
    LogLevel default_level;
    LogLevel debug_level;
};

}

#endif //ENJINSDK_LOGGERPROVIDER_HPP
