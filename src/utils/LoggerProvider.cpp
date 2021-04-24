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

#include "enjinsdk/LoggerProvider.hpp"

#include <stdexcept>
#include <utility>

namespace enjin::sdk::utils {

LoggerProvider::LoggerProvider(std::shared_ptr<ILogger> logger, LogLevel default_level, LogLevel debug_level)
        : logger(std::move(logger)), default_level(default_level), debug_level(debug_level) {
    if (this->logger == nullptr) {
        throw std::invalid_argument("Argument 'logger' for LoggerProvider must not be null.");
    }
}

void LoggerProvider::log(const std::string& message) {
    log(default_level, message);
}

void LoggerProvider::debug(const std::string& message) {
    log(debug_level, message);
}

void LoggerProvider::log(LogLevel level, const std::string& message) {
    if (logger->is_loggable(level)) {
        logger->log(level, message);
    }
}

void LoggerProvider::log(const std::string& message, const std::exception& e) {
    log(default_level, message, e);
}

void LoggerProvider::debug(const std::string& message, const std::exception& e) {
    log(debug_level, message, e);
}

void LoggerProvider::log(LogLevel level, const std::string& message, const std::exception& e) {
    if (logger->is_loggable(level)) {
        logger->log(level, message, e);
    }
}

const std::shared_ptr<ILogger>& LoggerProvider::get_logger() const {
    return logger;
}

LogLevel LoggerProvider::get_default_level() const {
    return default_level;
}

LogLevel LoggerProvider::get_debug_level() const {
    return debug_level;
}

}
