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

#ifndef ENJINSDK_LOGLEVEL_HPP
#define ENJINSDK_LOGLEVEL_HPP

namespace enjin::sdk::utils {

/// \brief Enum values dictating the severity level of a log message.
enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERR,
    SEVERE,
};

}

#endif //ENJINSDK_LOGLEVEL_HPP
