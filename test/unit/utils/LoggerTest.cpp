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

#include "enjinsdk/Logger.hpp"
#include "gtest/gtest.h"
#include <memory>
#include <string>

using namespace enjin::sdk::utils;

class LoggerTest : public testing::Test {
public:
    LoggerBuilder class_under_test;
};

TEST_F(LoggerTest, LoggerNameIsNotSetBuiltLoggerHasNameWithDefaultPrefix) {
    // Arrange
    const std::string expected_prefix("enjinsdk_logger_");

    // Act
    std::string actual = class_under_test.build()
                                         ->get_name();

    // Assert
    ASSERT_TRUE(actual.find(expected_prefix) == 0);
}

TEST_F(LoggerTest, LoggerNameIsSetBuiltLoggerHasExpectedName) {
    // Arrange
    const std::string expected("xyz");
    class_under_test.set_logger_name(expected);

    // Act
    std::string actual = class_under_test.build()
                                         ->get_name();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(LoggerTest, DoesNotEnableColorColorIsDisabledForBuiltLogger) {
    // Act
    auto logger = class_under_test.build();

    // Assert
    ASSERT_FALSE(logger->is_using_color());
}

TEST_F(LoggerTest, DoesEnableColorColorIsEnabledForBuiltLogger) {
    // Arrange
    class_under_test.enable_color();

    // Act
    auto logger = class_under_test.build();

    // Assert
    ASSERT_TRUE(logger->is_using_color());
}

TEST_F(LoggerTest, DoesNotEnableStdoutStdoutIsDisabledForBuiltLogger) {
    // Act
    auto logger = class_under_test.build();

    // Assert
    ASSERT_FALSE(logger->is_using_stdout());
}

TEST_F(LoggerTest, DoesEnableStdoutStdoutIsEnabledForBuiltLogger) {
    // Arrange
    class_under_test.enable_stdout();

    // Act
    auto logger = class_under_test.build();

    // Assert
    ASSERT_TRUE(logger->is_using_stdout());
}

TEST_F(LoggerTest, DoesNotEnableStderrStderrIsDisabledForBuiltLogger) {
    // Act
    auto logger = class_under_test.build();

    // Assert
    ASSERT_FALSE(logger->is_using_stderr());
}

TEST_F(LoggerTest, DoesEnableStderrStderrIsEnabledForBuiltLogger) {
    // Arrange
    class_under_test.enable_stderr();

    // Act
    auto logger = class_under_test.build();

    // Assert
    ASSERT_TRUE(logger->is_using_stderr());
}

TEST_F(LoggerTest, DefaultLevelIsNotSetBuiltLoggerHasInfoLevelAsDefault) {
    // Arrange
    const LogLevel expected = LogLevel::INFO;

    // Act
    LogLevel actual = class_under_test.build()
                                      ->get_default_level();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(LoggerTest, DefaultLevelIsSetBuiltLoggerHasExpectedValue) {
    // Arrange
    const LogLevel expected = LogLevel::SEVERE;
    class_under_test.set_default_level(expected);

    // Act
    LogLevel actual = class_under_test.build()
                                      ->get_default_level();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(LoggerTest, LogFileAddedBuiltLoggerHasLogFile) {
    // Arrange
    const std::string expected("dummy_log.txt");
    class_under_test.add_log_file(expected);

    // Act
    auto logger = class_under_test.build();

    // Assert
    ASSERT_TRUE(logger->is_using_log_file(expected));
}

TEST_F(LoggerTest, OutStreamAddedBuiltLoggerIsUsingLogFile) {
    // Arrange
    const std::shared_ptr<std::ostream> expected = std::make_shared<std::ostream>(nullptr);
    class_under_test.add_ostream(expected);

    // Act
    auto logger = class_under_test.build();

    // Assert
    ASSERT_TRUE(logger->is_using_ostream(expected));
}
