#ifndef ENJINSDK_LOGGER_HPP
#define ENJINSDK_LOGGER_HPP

#include "enjinsdk_export.h"
#include <memory>
#include <optional>
#include <ostream>
#include <set>
#include <string>
#include <utility>

namespace enjin::sdk::utils {

/// \brief Enum dictating the level of a log message.
enum class LogLevel {
    INFO,
    TRACE,
    DEBUG,
    WARN,
    ERR,
    SEVERE,
};

/// \brief Implementation of the logger used internally.
class ENJINSDK_EXPORT LoggerImpl;

class Logger;

/// \brief Builder class for Logger.
class ENJINSDK_EXPORT LoggerBuilder {
public:
    /// \brief Default constructor.
    LoggerBuilder() = default;

    /// \brief Default destructor.
    ~LoggerBuilder() = default;

    /// \brief Builds the logger and provides the unique pointer for it.
    /// \return The logger.
    std::unique_ptr<Logger> build();

    /// \brief Enables color on the logger for sinks which support the feature.
    /// \return This builder for chaining.
    LoggerBuilder& enable_color();

    /// \brief Enables the standard out stream to be used as a sink by the logger.
    /// \param pattern The pattern to be used by the sink.
    /// \return This builder for chaining.
    LoggerBuilder& enable_stdout(const std::string& pattern = "");

    /// \brief Enables the standard error stream to be used as a sink by the logger.
    /// \param pattern The pattern to be used by the sink.
    /// \return This builder for chaining.
    LoggerBuilder& enable_stderr(const std::string& pattern = "");

    /// \brief Adds a log file to be used as a sink by the logger.
    /// \param filename The filename.
    /// \param pattern The pattern to be used by the sink.
    /// \return This builder for chaining.
    LoggerBuilder& add_log_file(const std::string& filename, const std::string& pattern = "");

    /// \brief Adds an out stream to be used as a sink by the logger.
    /// \param ostream The stream.
    /// \param pattern The pattern to be used by the sink.
    /// \return This builder for chaining.
    LoggerBuilder& add_ostream(const std::shared_ptr<std::ostream>& ostream, const std::string& pattern = "");

    /// \brief Sets the name of the logger. Prefixed with "enjinsdk_logger" if unused.
    /// \param name The name.
    /// \return This builder for chaining.
    LoggerBuilder& set_logger_name(const std::string& name);

    /// \brief Sets the default log level to be used by the logger. Initialized as LogLevel::INFO if unused.
    /// \param level The log level.
    /// \return This builder for chaining.
    LoggerBuilder& set_default_level(LogLevel level);

private:
    std::optional<std::string> m_logger_name;
    bool use_color = false;
    std::optional<std::pair<bool, std::string>> m_use_stdout;
    std::optional<std::pair<bool, std::string>> m_use_stderr;
    std::set<std::pair<std::string, std::string>> log_filenames;
    std::set<std::pair<std::shared_ptr<std::ostream>, std::string>> ostreams;
    std::optional<LogLevel> m_default_level;
};

/// \brief Logger class for sending log messages to configured destinations.
/// \remarks Utilizes the spdlog library for its underlying implementation.
class ENJINSDK_EXPORT Logger {
public:
    /// \brief Default destructor.
    ~Logger() = default;

    /// \brief Logs the message at the default level.
    /// \param message The message.
    void log(const std::string& message);

    /// \brief Logs the message at the specified level.
    /// \param level The log level.
    /// \param message The message.
    void log(LogLevel level, const std::string& message);

    /// \brief Logs the message at the debug level.
    /// \param message The message.
    void debug(const std::string& message);

    /// \brief Determines if this logger is using the specified log file.
    /// \param filename The filename.
    /// \return Whether this logger is using the file.
    [[nodiscard]] bool is_using_log_file(const std::string& filename) const;

    /// \brief Determines if this logger is using the specified out stream.
    /// \param ostream The stream.
    /// \return Whether this logger is using the out stream.
    [[nodiscard]] bool is_using_ostream(const std::shared_ptr<std::ostream>& ostream) const;

    /// \brief Determines if this logger is using color for its sinks that support the feature.
    /// \return Whether this logger is using color.
    [[nodiscard]] bool is_using_color() const noexcept;

    /// \brief Determines if this logger is using the standard out stream.
    /// \return Whether this logger is using the standard out stream.
    [[nodiscard]] bool is_using_stdout() const noexcept;

    /// \brief Determines if this logger is using the standard error stream.
    /// \return Whether this logger is using the standard error stream.
    [[nodiscard]] bool is_using_stderr() const noexcept;

    /// \brief Returns the name of this logger.
    /// \return The name.
    [[nodiscard]] const std::string& get_name() const;

    /// \brief Returns the default log level of this logger.
    /// \return The default log level.
    [[nodiscard]] LogLevel get_default_level() const noexcept;

private:
    LogLevel default_level;

    std::shared_ptr<LoggerImpl> impl;

    Logger(const std::string& logger_name,
           const std::set<std::pair<std::string, std::string>>& log_filenames,
           const std::set<std::pair<std::shared_ptr<std::ostream>, std::string>>& ostreams,
           bool use_color,
           const std::pair<bool, std::string>& use_stdout,
           const std::pair<bool, std::string>& use_stderr,
           LogLevel default_level);

    friend std::unique_ptr<Logger> LoggerBuilder::build();
};

}

#endif //ENJINSDK_LOGGER_HPP
