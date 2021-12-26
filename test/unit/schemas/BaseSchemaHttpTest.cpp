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
#include "DummyObject.hpp"
#include "FakeGraphqlRequest.hpp"
#include "HttpClient.hpp"
#include "MockHttpServer.hpp"
#include "TestableBaseSchema.hpp"
#include <memory>
#include <sstream>
#include <string>

using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using namespace enjin::test::utils;

class BaseSchemaHttpTest : public testing::Test {
public:
    static constexpr HttpMethod HTTP_METHOD = HttpMethod::POST;
    static constexpr char DEFAULT_PATH_QUERY_FRAGMENT[] = "/graphql/test";
    static constexpr char JSON[] = "application/json; charset=utf-8";

    MockHttpServer mock_server;

    TestableBaseSchema create_testable_base_schema() {
        auto client = std::make_unique<http::HttpClient>(mock_server.uri());
        client->start();

        return TestableBaseSchema(TrustedPlatformMiddleware(std::move(client)));
    }

protected:
    void SetUp() override {
        mock_server.start();
    }

    void TearDown() override {
        mock_server.stop();
    }
};

TEST_F(BaseSchemaHttpTest, SendRequestForOneResponseIsSuccessfulReceivesExpected) {
    // Arrange - Data
    DummyObject expected = DummyObject::create_default_dummy_object();
    TestableBaseSchema schema = create_testable_base_schema();
    FakeGraphqlRequest fake_request(expected.serialize());
    std::string req_body = schema.create_request_body(fake_request);
    std::stringstream res_body;
    res_body << R"({"data":{"result":)"
             << expected.serialize()
             << R"(}})";
    HttpRequest http_req = HttpRequest().set_method(HTTP_METHOD)
                                        .set_path_query_fragment(DEFAULT_PATH_QUERY_FRAGMENT)
                                        .set_content_type(JSON)
                                        .set_body(req_body);
    HttpResponse http_res = HttpResponse::builder().code(200)
                                                   .content_type(JSON)
                                                   .body(res_body.str())
                                                   .build();

    // Arrange - Stubbing
    mock_server.given(http_req)
               .respond_with(http_res);

    // Act
    auto response = schema.send_request_for_one<DummyObject>(fake_request).get();

    // Assert
    ASSERT_EQ(expected, response.get_result().value());
}

TEST_F(BaseSchemaHttpTest, SendRequestForOneServerRespondsWithErrorReponseIsNotSuccessful) {
    // Arrange - Data
    TestableBaseSchema schema = create_testable_base_schema();
    DummyObject dummy_object = DummyObject::create_default_dummy_object();
    FakeGraphqlRequest fake_request(dummy_object.serialize());
    std::string req_body = schema.create_request_body(fake_request);
    HttpRequest http_req = HttpRequest().set_method(HTTP_METHOD)
                                        .set_path_query_fragment(DEFAULT_PATH_QUERY_FRAGMENT)
                                        .set_content_type(JSON)
                                        .set_body(req_body);
    HttpResponse http_res = HttpResponse::builder().code(400)
                                                   .content_type(JSON)
                                                   .body("Test Error Response")
                                                   .build();

    // Arrange - Stubbing
    mock_server.given(http_req)
               .respond_with(http_res);

    // Act
    auto response = schema.send_request_for_one<DummyObject>(fake_request).get();

    // Assert
    ASSERT_FALSE(response.is_successful());
}

TEST_F(BaseSchemaHttpTest, SendRequestForMany) {
    // Arrange - Data
    DummyObject expected = DummyObject::create_default_dummy_object();
    TestableBaseSchema schema = create_testable_base_schema();
    FakeGraphqlRequest fake_request(expected.serialize());
    std::string req_body = schema.create_request_body(fake_request);
    std::stringstream res_body;
    res_body << R"({"data":{"result":[)"
             << expected.serialize()
             << R"(,)"
             << expected.serialize()
             << R"(]}})";
    HttpRequest http_req = HttpRequest().set_method(HTTP_METHOD)
                                        .set_path_query_fragment(DEFAULT_PATH_QUERY_FRAGMENT)
                                        .set_content_type(JSON)
                                        .set_body(req_body);
    HttpResponse http_res = HttpResponse::builder().code(200)
                                                   .content_type(JSON)
                                                   .body(res_body.str())
                                                   .build();

    // Arrange - Stubbing
    mock_server.given(http_req)
               .respond_with(http_res);

    // Act
    auto response = schema.send_request_for_many<DummyObject>(fake_request).get();

    // Assert
    for (const auto& actual : response.get_result().value()) {
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(BaseSchemaHttpTest, SendRequestForManyServerRespondsWithErrorReponseIsNotSuccessful) {
    // Arrange - Data
    TestableBaseSchema schema = create_testable_base_schema();
    DummyObject dummy_object = DummyObject::create_default_dummy_object();
    FakeGraphqlRequest fake_request(dummy_object.serialize());
    std::string req_body = schema.create_request_body(fake_request);
    HttpRequest http_req = HttpRequest().set_method(HTTP_METHOD)
                                        .set_path_query_fragment(DEFAULT_PATH_QUERY_FRAGMENT)
                                        .set_content_type(JSON)
                                        .set_body(req_body);
    HttpResponse http_res = HttpResponse::builder().code(400)
                                                   .content_type(JSON)
                                                   .body("Test Error Response")
                                                   .build();

    // Arrange - Stubbing
    mock_server.given(http_req)
               .respond_with(http_res);

    // Act
    auto response = schema.send_request_for_one<DummyObject>(fake_request).get();

    // Assert
    ASSERT_FALSE(response.is_successful());
}
