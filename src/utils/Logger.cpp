#include "enjinsdk/Logger.hpp"

#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/ostream_sink.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <sstream>

namespace enjin::sdk::utils {

class LoggerImpl {
public:
    LoggerImpl() = delete;

    LoggerImpl(const std::string& logger_name,
               const std::set<std::pair<std::string, std::string>>& log_filenames,
               const std::set<std::pair<std::shared_ptr<std::ostream>, std::string>>& ostreams,
               bool use_color,
               const std::pair<bool, std::string>& use_stdout,
               const std::pair<bool, std::string>& use_stderr)
            : using_color(use_color),
              using_stdout(use_stdout.first),
              using_stderr(use_stderr.first) {
        logger = std::make_unique<spdlog::logger>(spdlog::logger(logger_name));

        // Add log files
        for (const auto& pair : log_filenames) {
            auto filename = pair.first;
            auto pattern = pair.second;
            auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);

            if (!pattern.empty()) {
                sink->set_pattern(pattern);
            }

            logger->sinks().push_back(sink);
            LoggerImpl::log_filenames.emplace(filename);
        }

        // Add out streams
        for (const auto& pair : ostreams) {
            auto ostream = pair.first;
            auto pattern = pair.second;
            auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(*ostream);

            if (!pattern.empty()) {
                sink->set_pattern(pattern);
            }

            logger->sinks().push_back(sink);
            LoggerImpl::ostreams.emplace(ostream);
        }

        // Enable stdout
        if (using_stdout) {
            auto pattern = use_stdout.second;

            if (use_color) {
                auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

                if (!pattern.empty()) {
                    sink->set_pattern(pattern);
                }

                logger->sinks().push_back(sink);
            } else {
                auto sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();

                if (!pattern.empty()) {
                    sink->set_pattern(pattern);
                }

                logger->sinks().push_back(sink);
            }
        }

        // Enable stderr
        if (using_stderr) {
            auto pattern = use_stderr.second;

            if (use_color) {
                auto sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();

                if (!pattern.empty()) {
                    sink->set_pattern(pattern);
                }

                logger->sinks().push_back(sink);
            } else {
                auto sink = std::make_shared<spdlog::sinks::stderr_sink_mt>();

                if (!pattern.empty()) {
                    sink->set_pattern(pattern);
                }

                logger->sinks().push_back(sink);
            }
        }
    };

    ~LoggerImpl() = default;

    void log(LogLevel level, const std::string& message) {
        switch (level) {
            case LogLevel::TRACE:
                logger->log(spdlog::level::trace, message);
                break;
            case LogLevel::DEBUG:
                logger->log(spdlog::level::debug, message);
                break;
            case LogLevel::WARN:
                logger->log(spdlog::level::warn, message);
                break;
            case LogLevel::ERR:
                logger->log(spdlog::level::err, message);
                break;
            case LogLevel::SEVERE:
                logger->log(spdlog::level::critical, message);
                break;
            default: // LogLevel::INFO
                logger->log(spdlog::level::info, message);
                break;
        }
    }

    [[nodiscard]] bool is_using_log_file(const std::string& filename) const {
        return log_filenames.find(filename) != log_filenames.end();;
    }

    [[nodiscard]] bool is_using_ostream(const std::shared_ptr<std::ostream>& ostream) const {
        return ostreams.find(ostream) != ostreams.end();
    }

    [[nodiscard]] bool is_using_color() const noexcept {
        return using_color;
    }

    [[nodiscard]] bool is_using_stdout() const noexcept {
        return using_stdout;
    }

    [[nodiscard]] bool is_using_stderr() const noexcept {
        return using_stderr;
    }

    [[nodiscard]] const std::string& get_name() const {
        return logger->name();
    }

    static std::string generate_next_logger_name() {
        std::stringstream ss;
        ss << LOGGER_PREFIX << (LoggerImpl::id++);
        return ss.str();
    }

    static std::pair<bool, std::string> default_std_stream_value() {
        return std::make_pair(false, "");
    }

private:
    std::set<std::string> log_filenames;
    std::set<std::shared_ptr<std::ostream>> ostreams;
    bool using_color;
    bool using_stdout;
    bool using_stderr;

    std::unique_ptr<spdlog::logger> logger;

    inline static unsigned int id = 0;
    static constexpr char LOGGER_PREFIX[] = "enjinsdk_logger_";
};

Logger::Logger(const std::string& logger_name,
               const std::set<std::pair<std::string, std::string>>& log_filenames,
               const std::set<std::pair<std::shared_ptr<std::ostream>, std::string>>& ostreams,
               bool use_color,
               const std::pair<bool, std::string>& use_stdout,
               const std::pair<bool, std::string>& use_stderr,
               LogLevel default_level)
        : default_level(default_level),
          impl(std::make_shared<LoggerImpl>(logger_name,
                                            log_filenames,
                                            ostreams,
                                            use_color,
                                            use_stdout,
                                            use_stderr)) {
}

void Logger::log(const std::string& message) {
    log(default_level, message);
}

void Logger::log(LogLevel level, const std::string& message) {
    impl->log(level, message);
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

bool Logger::is_using_log_file(const std::string& filename) const {
    return impl->is_using_log_file(filename);
}

bool Logger::is_using_ostream(const std::shared_ptr<std::ostream>& ostream) const {
    return impl->is_using_ostream(ostream);
}

bool Logger::is_using_color() const noexcept {
    return impl->is_using_color();
}

bool Logger::is_using_stdout() const noexcept {
    return impl->is_using_stdout();
}

bool Logger::is_using_stderr() const noexcept {
    return impl->is_using_stderr();
}

const std::string& Logger::get_name() const {
    return impl->get_name();
}

LogLevel Logger::get_default_level() const noexcept {
    return default_level;
}

Logger LoggerBuilder::build() {
    auto logger_name = m_logger_name.value_or(LoggerImpl::generate_next_logger_name());
    auto use_stdout = m_use_stdout.value_or(LoggerImpl::default_std_stream_value());
    auto use_stderr = m_use_stderr.value_or(LoggerImpl::default_std_stream_value());
    auto default_level = m_default_level.value_or(LogLevel::INFO);

    return Logger(logger_name,
                  log_filenames,
                  ostreams,
                  use_color,
                  use_stdout,
                  use_stderr,
                  default_level);
}

LoggerBuilder& LoggerBuilder::enable_color() {
    use_color = true;
    return *this;
}

LoggerBuilder& LoggerBuilder::enable_stdout(const std::string& pattern) {
    m_use_stdout = std::make_pair(true, pattern);
    return *this;
}

LoggerBuilder& LoggerBuilder::enable_stderr(const std::string& pattern) {
    m_use_stderr = std::make_pair(true, pattern);
    return *this;
}

LoggerBuilder& LoggerBuilder::add_log_file(const std::string& filename, const std::string& pattern) {
    log_filenames.emplace(std::make_pair(filename, pattern));
    return *this;
}

LoggerBuilder& LoggerBuilder::add_ostream(const std::shared_ptr<std::ostream>& ostream, const std::string& pattern) {
    ostreams.emplace(std::make_pair(ostream, pattern));
    return *this;
}

LoggerBuilder& LoggerBuilder::set_logger_name(const std::string& name) {
    m_logger_name = name;
    return *this;
}

LoggerBuilder& LoggerBuilder::set_default_level(LogLevel level) {
    m_default_level = level;
    return *this;
}

}
