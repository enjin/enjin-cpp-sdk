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
#include "FakeGraphqlRequest.hpp"
#include "MockHttpClient.hpp"
#include "TestableBaseSchema.hpp"
#include <string>

using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using namespace enjin::test::utils;

class BaseSchemaTest : public testing::Test {
public:
    std::unique_ptr<TestableBaseSchema> class_under_test;

protected:
    void SetUp() override {
        testing::Test::SetUp();

        class_under_test = std::make_unique<TestableBaseSchema>(std::make_unique<MockHttpClient>());
    }
};

TEST_F(BaseSchemaTest, CreateRequestBody) {
    // Arrange
    const std::string expected(R"({"query":"","variables":{"var":1}})");
    FakeGraphqlRequest fake_request(R"({"var":1})");

    // Act
    const std::string actual = class_under_test->create_request_body(fake_request);

    // Asert
    ASSERT_EQ(expected, actual);
}
