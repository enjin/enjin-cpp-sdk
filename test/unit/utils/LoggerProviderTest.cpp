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
#include <stdexcept>

using namespace enjin::sdk::utils;
using namespace enjin::test::mocks;
using namespace enjin::test::suites;
using ::testing::AtLeast;
using ::testing::Return;

class LoggerProviderTest : public LoggerProviderTestSuite,
                           public testing::Test {
public:
    std::unique_ptr<LoggerProvider> class_under_test;

protected:
    void SetUp() override {
        mock_logger = std::make_shared<MockLogger>();
        class_under_test = std::make_unique<LoggerProvider>(mock_logger);
    }
};

TEST_F(LoggerProviderTest, LogGivenMessageLogsDataAtDefaultLevel) {
    // Arrange - Data
    const LogLevel level = class_under_test->get_default_level();
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
    class_under_test->log(message);

    // Verify (done by GTest)
}

TEST_F(LoggerProviderTest, DebugGivenMessageLogsDataAtDebugLevel) {
    // Arrange - Data
    const LogLevel level = class_under_test->get_debug_level();
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
    class_under_test->debug(message);

    // Verify (done by GTest)
}

TEST_F(LoggerProviderTest, LogGivenMessageAndExceptionLogsDataAtDefaultLevel) {
    // Arrange - Data
    const LogLevel level = class_under_test->get_default_level();
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
    class_under_test->log(message, e);

    // Verify (done by GTest)
}

TEST_F(LoggerProviderTest, DebugGivenMessageAndExceptionLogsDataAtDebugLevel) {
    // Arrange - Data
    const LogLevel level = class_under_test->get_debug_level();
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
    class_under_test->debug(message, e);

    // Verify (done by GTest)
}
