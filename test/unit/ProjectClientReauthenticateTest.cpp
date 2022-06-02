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

#include "HttpClient.hpp"
#include "MockHttpServer.hpp"
#include "RapidJsonUtils.hpp"
#include "enjinsdk/HttpHeaders.hpp"
#include "enjinsdk/ProjectClient.hpp"
#include "enjinsdk/models/AccessToken.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "rapidjson/document.h"
#include <chrono>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

using enjin::sdk::models::AccessToken;
using testing::MockFunction;
using testing::NiceMock;
using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::sdk::utils;
using namespace enjin::test::mocks;

class ProjectClientReauthenticateTestSuite {
public:
    static constexpr char FAKE_UUID[] = "Fake Uuid";
    static constexpr char FAKE_SECRET[] = "Fake Secret";
    static constexpr char JSON[] = "application/json; charset=utf-8";

    static AccessToken create_fake_access_token(const std::string& token, long expires_in) {
        auto access_token = AccessToken();
        auto ss = std::stringstream();

        ss << R"({"accessToken":")" << token << R"(","expiresIn":)" << expires_in << "}";
        access_token.deserialize(ss.str());

        return access_token;
    }

    static std::string serialize_token(const AccessToken& access_token) {
        rapidjson::Document document(rapidjson::kObjectType);

        const auto& token = access_token.get_token();
        if (token.has_value()) {
            set_string_member(document, "accessToken", token.value());
        }
        const auto& expires_in = access_token.get_expires_in();
        if (expires_in.has_value()) {
            set_integer_member(document, "expiresIn", expires_in.value());
        }

        return document_to_string(document);
    }
};

class ProjectClientReauthenticateTest : public ProjectClientReauthenticateTestSuite,
                                        public testing::Test {
public:
    std::unique_ptr<ProjectClient> class_under_test;

    NiceMock<MockFunction<void()>> mock_reauthentication_stopped_handler;

    MockHttpServer mock_server;

protected:
    void SetUp() override {
        mock_server.start();
        class_under_test = ProjectClient::builder()
                .http_client(std::make_unique<HttpClient>(mock_server.uri()))
                .enable_automatic_reauthentication()
                .reauthentication_stopped_handler(mock_reauthentication_stopped_handler.AsStdFunction())
                .build();
    }

    void TearDown() override {
        class_under_test.reset();
        mock_server.stop();
    }
};

class ProjectClientReauthenticateTestInvalidDurations : public ProjectClientReauthenticateTestSuite,
                                                        public testing::TestWithParam<long> {
public:
    std::unique_ptr<ProjectClient> class_under_test;

    NiceMock<MockFunction<void()>> mock_reauthentication_stopped_handler;

    MockHttpServer mock_server;

protected:
    void SetUp() override {
        mock_server.start();
        class_under_test = ProjectClient::builder()
                .http_client(std::make_unique<HttpClient>(mock_server.uri()))
                .enable_automatic_reauthentication()
                .reauthentication_stopped_handler(mock_reauthentication_stopped_handler.AsStdFunction())
                .build();
    }

    void TearDown() override {
        class_under_test.reset();
        mock_server.stop();
    }
};

TEST_F(ProjectClientReauthenticateTest, AuthWhileUuidAndSecretAreEmptyDoesNotStartReauthenticationTimer) {
    // Arrange
    const AccessToken fakeToken = create_fake_access_token("xyz", 1000L);

    // Assumption
    ASSERT_TRUE(class_under_test->is_automatic_reauthentication_enabled()) << "Automatic reauthentication is disabled.";
    ASSERT_FALSE(class_under_test->is_reauthentication_running()) << "Timer is running before call to authenticate.";

    // Act
    class_under_test->auth(fakeToken);

    // Assert
    ASSERT_FALSE(class_under_test->is_reauthentication_running()) << "Timer is running after call to authenticate.";
}

TEST_F(ProjectClientReauthenticateTest, AuthProjectGivenValidUuidAndSecretClientReauthenticates) {
    // Arrange - Data
    const std::string auth_token("FakeAuthToken");
    const std::string expected_path = "/graphql/project";
    const std::string expected_header = Authorization;
    const std::string expected_header_value = "Bearer " + auth_token;
    const Request request = Request::create().with_path(expected_path).using_post();
    const AccessToken fake_token = create_fake_access_token(auth_token, 1);
    const std::string response_body = R"({"data":{"result":)" + serialize_token(fake_token) + "}}";

    // Arrange - Mocking
    mock_server.given(request)
               .respond_with(Response::create()
                                     .with_success()
                                     .with_header(ContentType, JSON)
                                     .with_body(response_body));

    // Assumption
    ASSERT_TRUE(class_under_test->is_automatic_reauthentication_enabled()) << "Automatic reauthentication is disabled.";
    ASSERT_FALSE(class_under_test->is_authenticated()) << "Is authenticated before request is sent.";

    // Act
    auto future = class_under_test->auth_client(FAKE_UUID, FAKE_SECRET);

    future.wait_for(std::chrono::milliseconds(1000));
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // Assert
    ASSERT_NO_THROW(future.get()) << "AuthClient operation resulted in an error.";
    ASSERT_TRUE(class_under_test->is_authenticated()) << "Client was not authenticated.";

    // Verify
    auto log_entries = mock_server.find_received_requests(request);
    ASSERT_GT(log_entries.size(), 1) << "Did not receive more than one request.";

    const auto& req1 = log_entries[0].get_request_message().value();
    const auto& req1_headers = req1.get_headers();
    ASSERT_EQ(req1.get_path(), expected_path) << "Req1 is not to the expected path.";
    ASSERT_FALSE(req1_headers.find(expected_header) != req1_headers.end()) << "Req1 had authorization.";

    const auto& req2 = log_entries[1].get_request_message().value();
    const auto& req2_headers = req2.get_headers();
    ASSERT_EQ(req2.get_path(), expected_path) << "Req2 is not to the expected path.";
    ASSERT_EQ(req2_headers.at(expected_header), expected_header_value) << "Req2 did not have authorization.";
}

TEST_F(ProjectClientReauthenticateTest, AuthGivenEmptyTokenStopsReauthenticationTimer) {
    // Arrange - Data
    const AccessToken empty_token;
    const AccessToken fake_token = create_fake_access_token("xyz", 1000L);
    const std::string response_body = R"({"data":{"result":)" + serialize_token(fake_token) + "}}";

    // Arrange - Expectations
    EXPECT_CALL(mock_reauthentication_stopped_handler, Call()).Times(1);

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path("/graphql/project")
                              .using_post())
               .respond_with(Response::create()
                                     .with_success()
                                     .with_header(ContentType, JSON)
                                     .with_body(response_body));

    // Arrange - Data (continued)
    class_under_test->auth_client(FAKE_UUID, FAKE_SECRET).wait_for(std::chrono::milliseconds(1000));

    // Assumption
    ASSERT_TRUE(class_under_test->is_authenticated()) << "Is not authenticated.";
    ASSERT_TRUE(class_under_test->is_reauthentication_running()) << "Reauthentication is not running.";

    // Act
    class_under_test->auth(empty_token);

    // Assert
    ASSERT_FALSE(class_under_test->is_reauthentication_running()) << "Reauthentication is still running.";

    // Verify (done by GTest)
}

TEST_P(ProjectClientReauthenticateTestInvalidDurations, AuthGivenInvalidDurationStopsReauthenticationTimer) {
    // Arrange - Data
    const long expires_in = GetParam();
    const AccessToken bad_token = create_fake_access_token("xyz", expires_in);
    const AccessToken fake_token = create_fake_access_token("xyz", 1000L);
    const std::string response_body = R"({"data":{"result":)" + serialize_token(fake_token) + "}}";

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path("/graphql/project")
                              .using_post())
               .respond_with(Response::create()
                                     .with_success()
                                     .with_header(ContentType, JSON)
                                     .with_body(response_body));

    // Arrange - Expectations
    EXPECT_CALL(mock_reauthentication_stopped_handler, Call()).Times(1);

    // Arrange - Data (continued)
    class_under_test->auth_client(FAKE_UUID, FAKE_SECRET).wait_for(std::chrono::milliseconds(1000));

    // Assumption
    ASSERT_TRUE(class_under_test->is_authenticated()) << "Is not authenticated.";
    ASSERT_TRUE(class_under_test->is_reauthentication_running()) << "Reauthentication is not running.";

    // Act
    class_under_test->auth(bad_token);

    // Assert
    ASSERT_FALSE(class_under_test->is_reauthentication_running()) << "Reauthentication is still running.";

    // Verify (done by GTest)
}

INSTANTIATE_TEST_SUITE_P(InvalidDurations,
                         ProjectClientReauthenticateTestInvalidDurations,
                         testing::Values(0L, -1L, -100L));
