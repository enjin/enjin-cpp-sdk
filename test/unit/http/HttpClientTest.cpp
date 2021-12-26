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

#include "gtest/gtest.h"
#include "HttpClient.hpp"
#include "MockHttpServer.hpp"
#include "VerificationTestSuite.hpp"
#include "enjinsdk/HttpHeaders.hpp"
#include <stdexcept>

using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using namespace enjin::test::suites;

class HttpClientTest : public VerificationTestSuite,
                       public testing::Test {
public:
    static constexpr char JSON[] = "application/json; charset=utf-8";

    MockHttpServer mock_server;

    HttpClient create_client() {
        return HttpClient(mock_server.uri());
    }

    static HttpRequest create_default_request() {
        return HttpRequest().set_method(HttpMethod::POST)
                            .set_path_query_fragment("/")
                            .set_content_type(JSON)
                            .set_body("{}");
    }

protected:
    void SetUp() override {
        mock_server.start();
    }

    void TearDown() override {
        mock_server.stop();
    }
};

TEST_F(HttpClientTest, SendRequestReceivesSuccessfulResponseAndReturnsExpected) {
    // Arrange - Data
    const unsigned short expected_code = 200;
    const std::string expected_body = "{}";
    const std::string expected_content_type = JSON;
    HttpClient client = create_client();
    HttpRequest dummy_request = create_default_request();
    client.start();

    // Arrange - Stubbing
    mock_server.given(dummy_request)
               .respond_with(HttpResponse::builder()
                                     .code(expected_code)
                                     .body(expected_body)
                                     .add_header(CONTENT_TYPE, expected_content_type)
                                     .build());

    // Act
    HttpResponse response = client.send_request(dummy_request).get();

    // Assert
    EXPECT_EQ(expected_code, response.get_code().value());
    EXPECT_EQ(expected_body, response.get_body().value());
    EXPECT_EQ(expected_content_type, response.get_header_value(CONTENT_TYPE).value());
}

TEST_F(HttpClientTest, SendRequestReceivesErrorResponseAndThrowsError) {
    // Arrange - Data
    HttpClient client = create_client();
    HttpRequest dummy_request = create_default_request();
    client.start();
    mock_server.stop();

    // Act
    auto future = client.send_request(dummy_request);

    // Assert
    ASSERT_THROW(future.get(), std::runtime_error);
}
