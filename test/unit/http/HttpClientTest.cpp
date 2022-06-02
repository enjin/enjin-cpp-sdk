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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "HttpClient.hpp"
#include "MockHttpServer.hpp"
#include "MockLogger.hpp"
#include "VerificationTestSuite.hpp"
#include "enjinsdk/HttpHeaders.hpp"
#include <memory>
#include <string>

using namespace enjin::sdk::http;
using namespace enjin::sdk::utils;
using namespace enjin::test::mocks;
using namespace enjin::test::suites;
using ::testing::An;
using ::testing::AtLeast;
using ::testing::Mock;
using ::testing::Return;

class HttpClientSuite : public VerificationTestSuite {
public:
    static constexpr char JSON[] = "application/json; charset=utf-8";

    static HttpRequest create_dummy_request() {
        return HttpRequest().set_method(HttpMethod::POST)
                            .set_path_query_fragment("/")
                            .set_content_type(JSON)
                            .set_body("{}");
    }
};

class HttpClientTest : public HttpClientSuite,
                       public testing::Test {
public:
    std::unique_ptr<HttpClient> class_under_test;

    MockHttpServer mock_server;

protected:
    void SetUp() override {
        mock_server.start();
        class_under_test = std::make_unique<HttpClient>(mock_server.uri());
    }

    void TearDown() override {
        mock_server.stop();
    }
};

class HttpClientLoggingTest : public HttpClientSuite,
                              public testing::TestWithParam<HttpLogLevel> {
public:
    std::unique_ptr<HttpClient> class_under_test;

    MockHttpServer mock_server;

protected:
    void SetUp() override {
        mock_server.start();
        class_under_test = std::make_unique<HttpClient>(mock_server.uri());
    }

    void TearDown() override {
        mock_server.stop();
    }
};

TEST_F(HttpClientTest, SendRequestReceivesSuccessfulResponseAndReturnsExpected) {
    // Arrange - Data
    const int expected_code = 200;
    const std::string expected_body = "{}";
    const std::string expected_content_type = JSON;
    const HttpRequest dummy_request = create_dummy_request();
    class_under_test->start();

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path("/")
                              .with_body("{}")
                              .using_post())
               .respond_with(Response::create()
                                     .with_status_code(expected_code)
                                     .with_header(CONTENT_TYPE, expected_content_type)
                                     .with_body(expected_body));

    // Act
    HttpResponse response = class_under_test->send_request(dummy_request).get();

    // Assert
    EXPECT_EQ(expected_code, response.get_code().value());
    EXPECT_EQ(expected_body, response.get_body().value());
    EXPECT_EQ(expected_content_type, response.get_header_value(CONTENT_TYPE).value());
}

TEST_F(HttpClientTest, SetDefaultRequestHeaderSentRequestHasHeader) {
    // Arrange - Data
    const std::string expected_header_key("Test Header");
    const std::string expected_header_value("Test Value");
    const HttpRequest dummy_request = create_dummy_request();
    class_under_test->start();
    class_under_test->set_default_request_header(expected_header_key, expected_header_value);

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path("/")
                              .with_body("{}")
                              .using_post())
               .respond_with(Response::create()
                                     .with_success()
                                     .with_header(CONTENT_TYPE, JSON)
                                     .with_body("{}"));

    // Arrange - Expectations
    mock_server.next_message([this, expected_header_key, expected_header_value](const HttpRequest& req) {
        increment_call_counter();

        auto actual = req.get_header_value(expected_header_key);
        EXPECT_TRUE(actual.has_value());
        EXPECT_EQ(expected_header_value, actual.value());
    });
    set_expected_call_count(1);

    // Act
    HttpResponse response = class_under_test->send_request(dummy_request).get();

    // Verify
    verify_call_count(1);

    // Assert (see: Arrange - Expectations)
}

TEST_F(HttpClientTest, SetLoggerHttpLogLevelIsNoneExpectNoLogs) {
    // Arrange - Data
    const HttpLogLevel log_level = HttpLogLevel::None;
    const HttpRequest dummy_request = create_dummy_request();
    std::shared_ptr<NiceMockLogger> mock_logger = std::make_shared<NiceMockLogger>();
    class_under_test->start();
    class_under_test->set_logger(log_level, std::make_shared<LoggerProvider>(mock_logger));

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path("/")
                              .with_body("{}")
                              .using_post())
               .respond_with(Response::create()
                                     .with_success()
                                     .with_header(CONTENT_TYPE, JSON)
                                     .with_body("{}"));
    ON_CALL(*mock_logger, is_loggable(An<LogLevel>()))
            .WillByDefault(Return(true));

    // Arrange - Expectations
    EXPECT_CALL(*mock_logger, log(An<LogLevel>(), An<const std::string&>()))
            .Times(0);

    // Act
    class_under_test->send_request(dummy_request).get();

    // Verify
    Mock::VerifyAndClearExpectations(mock_logger.get());
}

TEST_P(HttpClientLoggingTest, SetLoggerHttpLogLevelIsNotNoneExpectLogs) {
    // Arrange - Data
    const HttpLogLevel log_level = GetParam();
    const HttpRequest dummy_request = create_dummy_request();
    std::shared_ptr<NiceMockLogger> mock_logger = std::make_shared<NiceMockLogger>();
    class_under_test->start();
    class_under_test->set_logger(log_level, std::make_shared<LoggerProvider>(mock_logger));

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path("/")
                              .with_body("{}")
                              .using_post())
               .respond_with(Response::create()
                                     .with_success()
                                     .with_header(CONTENT_TYPE, JSON)
                                     .with_body("{}"));
    ON_CALL(*mock_logger, is_loggable(An<LogLevel>()))
            .WillByDefault(Return(true));

    // Arrange - Expectations
    EXPECT_CALL(*mock_logger, log(An<LogLevel>(), An<const std::string&>()))
            .Times(AtLeast(2));

    // Act
    class_under_test->send_request(dummy_request).get();

    // Verify
    Mock::VerifyAndClearExpectations(mock_logger.get());
}

INSTANTIATE_TEST_SUITE_P(HttpClientLoggingLevels,
                         HttpClientLoggingTest,
                         testing::Values(HttpLogLevel::Basic,
                                         HttpLogLevel::Headers,
                                         HttpLogLevel::Body));
