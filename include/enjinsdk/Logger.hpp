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

#ifndef ENJINSDK_LOGGER_HPP
#define ENJINSDK_LOGGER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ILogger.hpp"
#include <string>

namespace enjin::sdk::utils {

/// \brief Basic logger class for logging messages to stdout.
class ENJINSDK_EXPORT Logger : public ILogger {
public:
    /// \brief Default constructor.
    Logger();

    ~Logger() override;

    void log(LogLevel level, const std::string& message) override;

    void log(LogLevel level, const std::string& message, const std::exception& e) override;

    [[nodiscard]] bool is_loggable(LogLevel level) const override;

private:
    class Impl;

    Impl* impl;
};

}

#endif //ENJINSDK_LOGGER_HPP
