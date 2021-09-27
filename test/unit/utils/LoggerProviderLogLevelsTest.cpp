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

#include "LoggerProviderTestSuite.hpp"
#include "Matchers.hpp"
#include "enjinsdk/LoggerProvider.hpp"
#include <memory>

using namespace enjin::sdk::utils;
using namespace enjin::test::mocks;
using namespace enjin::test::suites;
using ::testing::AtLeast;
using ::testing::Return;

class LoggerProviderLogLevelsTest : public LoggerProviderTestSuite,
                                    public testing::TestWithParam<LogLevel> {
public:
    std::unique_ptr<LoggerProvider> class_under_test;

protected:
    void SetUp() override {
        mock_logger = std::make_shared<MockLogger>();
        class_under_test = std::make_unique<LoggerProvider>(mock_logger);
    }
};

TEST_P(LoggerProviderLogLevelsTest, LogGivenMessageWithLoggableLevelLogsDataAtGivenLevel) {
    // Arrange - Data
    const LogLevel level = GetParam();
    const std::string message(DEFAULT_MESSAGE);

    // Arrange - Stubbing
    ON_CALL(*mock_logger, is_loggable(level))
            .WillByDefault(Return(true));

    // Arrange - Expectations
    EXPECT_CALL(*mock_logger, is_loggable(level))
            .Times(AtLeast(1));
    EXPECT_CALL(*mock_logger, log(level, message))
            .Times(AtLeast(1));

    // Act
    class_under_test->log(level, message);

    // Verify (done by GTest)
}

TEST_P(LoggerProviderLogLevelsTest, LogGivenMessageWithNonLoggableLevelDoesNotLogData) {
    // Arrange - Data
    const LogLevel level = GetParam();
    const std::string message(DEFAULT_MESSAGE);

    // Arrange - Stubbing
    ON_CALL(*mock_logger, is_loggable(level))
            .WillByDefault(Return(false));

    // Arrange - Expectations
    EXPECT_CALL(*mock_logger, is_loggable(level))
            .Times(AtLeast(1));
    EXPECT_CALL(*mock_logger, log(level, message))
            .Times(0);

    // Act
    class_under_test->log(level, message);

    // Verify (done by GTest)
}

TEST_P(LoggerProviderLogLevelsTest, LogGivenMessageAndExceptionWithLoggableLevelLogsDataAtGivenLevel) {
    // Arrange - Data
    const LogLevel level = GetParam();
    const std::string message(DEFAULT_MESSAGE);
    const std::exception e = create_default_exception();

    // Arrange - Stubbing
    ON_CALL(*mock_logger, is_loggable(level))
            .WillByDefault(Return(true));

    // Arrange - Expectations
    EXPECT_CALL(*mock_logger, is_loggable(level))
            .Times(AtLeast(1));
    EXPECT_CALL(*mock_logger, log(level, message, ExEq(e)))
            .Times(AtLeast(1));

    // Act
    class_under_test->log(level, message, e);

    // Verify (done by GTest)
}

TEST_P(LoggerProviderLogLevelsTest, LogGivenMessageAndExceptionWithNonLoggableLevelDoesNotLogData) {
    // Arrange - Data
    const LogLevel level = GetParam();
    const std::string message(DEFAULT_MESSAGE);
    const std::exception e = create_default_exception();

    // Arrange - Stubbing
    ON_CALL(*mock_logger, is_loggable(level))
            .WillByDefault(Return(false));

    // Arrange - Expectations
    EXPECT_CALL(*mock_logger, is_loggable(level))
            .Times(AtLeast(1));
    EXPECT_CALL(*mock_logger, log(level, message, ExEq(e)))
            .Times(0);

    // Act
    class_under_test->log(level, message, e);

    // Verify (done by GTest)
}

INSTANTIATE_TEST_SUITE_P(LogLevels,
                         LoggerProviderLogLevelsTest,
                         testing::Values(LogLevel::TRACE,
                                         LogLevel::DEBUG,
                                         LogLevel::INFO,
                                         LogLevel::WARN,
                                         LogLevel::ERR,
                                         LogLevel::SEVERE));
