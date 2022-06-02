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

#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::http;
using namespace enjin::sdk::utils;

class HttpMethodTest : public testing::TestWithParam<std::tuple<std::string, HttpMethod>> {
};

TEST_P(HttpMethodTest, DeserializeEventTypeReturnsExpectedValue) {
    // Arrange
    const HttpMethod expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    HttpMethod actual = deserialize_http_method(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(HttpMethodTest, SerializeEventTypeReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    const HttpMethod value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_http_method(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableEventType,
                         HttpMethodTest,
                         testing::Values(std::make_tuple("GET", HttpMethod::Get),
                                         std::make_tuple("HEAD", HttpMethod::Head),
                                         std::make_tuple("POST", HttpMethod::Post),
                                         std::make_tuple("PUT", HttpMethod::Put),
                                         std::make_tuple("DELETE", HttpMethod::Delete),
                                         std::make_tuple("CONNECT", HttpMethod::Connect),
                                         std::make_tuple("OPTIONS", HttpMethod::Options),
                                         std::make_tuple("TRACE", HttpMethod::Trace),
                                         std::make_tuple("PATCH", HttpMethod::Patch)));
