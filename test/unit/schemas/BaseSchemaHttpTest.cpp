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
#include "enjinsdk/HttpHeaders.hpp"
#include <memory>
#include <string>

using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using namespace enjin::test::utils;

class BaseSchemaHttpTest : public testing::Test {
public:
    MockHttpServer mock_server;

    static constexpr char DEFAULT_PATH_QUERY_FRAGMENT[] = "/graphql/test";
    static constexpr char JSON[] = "application/json; charset=utf-8";

    TestableBaseSchema create_testable_base_schema() {
        auto client = std::make_unique<HttpClient>(mock_server.uri());
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

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path(DEFAULT_PATH_QUERY_FRAGMENT)
                              .with_body(schema.create_request_body(fake_request))
                              .using_post())
               .respond_with(Response::create()
                                     .with_success()
                                     .with_header(CONTENT_TYPE, {JSON})
                                     .with_body(R"({"data":{"result":)" + expected.serialize() + "}}"));

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

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path(DEFAULT_PATH_QUERY_FRAGMENT)
                              .with_body(schema.create_request_body(fake_request))
                              .using_post())
               .respond_with(Response::create()
                                     .with_status_code(400)
                                     .with_header(CONTENT_TYPE, {JSON})
                                     .with_body("Test Error Response"));

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

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path(DEFAULT_PATH_QUERY_FRAGMENT)
                              .with_body(schema.create_request_body(fake_request))
                              .using_post())
               .respond_with(Response::create()
                                     .with_success()
                                     .with_header(CONTENT_TYPE, JSON)
                                     .with_body(R"({"data":{"result":[)" +
                                                expected.serialize() +
                                                "," +
                                                expected.serialize() +
                                                "]}}"));

    // Act
    auto response = schema.send_request_for_many<DummyObject>(fake_request).get();

    // Assert
    for (const auto& actual: response.get_result().value()) {
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(BaseSchemaHttpTest, SendRequestForManyServerRespondsWithErrorReponseIsNotSuccessful) {
    // Arrange - Data
    TestableBaseSchema schema = create_testable_base_schema();
    DummyObject dummy_object = DummyObject::create_default_dummy_object();
    FakeGraphqlRequest fake_request(dummy_object.serialize());

    // Arrange - Stubbing
    mock_server.given(Request::create()
                              .with_path(DEFAULT_PATH_QUERY_FRAGMENT)
                              .with_body(schema.create_request_body(fake_request))
                              .using_post())
               .respond_with(Response::create()
                                     .with_status_code(400)
                                     .with_header(CONTENT_TYPE, JSON)
                                     .with_body("Test Error Response"));

    // Act
    auto response = schema.send_request_for_one<DummyObject>(fake_request).get();

    // Assert
    ASSERT_FALSE(response.is_successful());
}
