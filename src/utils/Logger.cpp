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

#include "enjinsdk/Logger.hpp"

#include "spdlog/logger.h"
#include "spdlog/sinks/stdout_sinks.h"
#include <memory>
#include <sstream>

namespace enjin::sdk::utils {

static unsigned int id = 0;

class Logger::Impl : ILogger {
public:
    Impl() {
        logger = spdlog::stdout_logger_st(generate_next_logger_name());
        logger->set_pattern("%H:%M:%S [%l] %v");
    };

    ~Impl() override = default;

    void log(LogLevel level, const std::string& message) override {
        logger->log(convert_log_level(level), message);
    }

    void log(LogLevel level, const std::string& message, const std::exception& e) override {
        std::stringstream ss;
        ss << message << " " << e.what();

        log(level, ss.str());
    }

    [[nodiscard]] bool is_loggable(LogLevel level) const override {
        return logger->should_log(convert_log_level(level));
    }

private:
    std::shared_ptr<spdlog::logger> logger;

    static constexpr char LOGGER_PREFIX[] = "enjinsdk_logger_";

    static spdlog::level::level_enum convert_log_level(LogLevel level) {
        switch (level) {
            case LogLevel::TRACE:
                return spdlog::level::trace;
            case LogLevel::DEBUG:
                return spdlog::level::debug;
            case LogLevel::INFO:
                return spdlog::level::info;
            case LogLevel::WARN:
                return spdlog::level::warn;
            case LogLevel::ERR:
                return spdlog::level::err;
            case LogLevel::SEVERE:
                return spdlog::level::critical;
            default:
                return spdlog::level::off;
        }
    }

    static std::string generate_next_logger_name() {
        std::stringstream ss;
        ss << LOGGER_PREFIX << (id++);
        return ss.str();
    }
};

Logger::Logger() : impl(new Impl()) {
}

Logger::~Logger() {
    delete impl;
}

void Logger::log(LogLevel level, const std::string& message) {
    impl->log(level, message);
}

void Logger::log(LogLevel level, const std::string& message, const std::exception& e) {
    impl->log(level, message, e);
}

bool Logger::is_loggable(LogLevel level) const {
    return impl->is_loggable(level);
}

}
