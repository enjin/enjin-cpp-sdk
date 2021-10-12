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

#include "enjinsdk/HttpResponse.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::http;

class HttpResponseBuilderTest : public testing::Test {
public:
    HttpResponse::HttpResponseBuilder class_under_test = HttpResponse::builder();
};

TEST_F(HttpResponseBuilderTest, BuildDoesNotThrowException) {
    // Arrange
    ASSERT_NO_THROW(HttpResponse response = class_under_test.build());
}

TEST_F(HttpResponseBuilderTest, BuildNoSetValuesBuiltRequestIsEmpty) {
    // Act
    HttpResponse actual = class_under_test.build();

    // Arrange
    EXPECT_FALSE(actual.get_body().has_value());
    EXPECT_FALSE(actual.get_content_type().has_value());
}

TEST_F(HttpResponseBuilderTest, CodeValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const uint16_t expected = 100;

    // Act
    uint16_t actual = class_under_test.code(expected)
                                      .build()
                                      .get_code()
                                      .value();

    // Arrange
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpResponseBuilderTest, BodyValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected("expected");

    // Act
    std::string actual = class_under_test.body(expected)
                                         .build()
                                         .get_body()
                                         .value();

    // Arrange
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpResponseBuilderTest, ContentTypeValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected("expected");

    // Act
    std::string actual = class_under_test.content_type(expected)
                                         .build()
                                         .get_content_type()
                                         .value();

    // Arrange
    ASSERT_EQ(expected, actual);
}
