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

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class WhitelistedTest : public testing::TestWithParam<std::tuple<std::string, Whitelisted>> {
};

TEST_P(WhitelistedTest, SerializeWhitelistedReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    Whitelisted value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_whitelisted(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeWhitelisted,
                         WhitelistedTest,
                         testing::Values(std::make_tuple("NONE", Whitelisted::None),
                                         std::make_tuple("SEND_AND_RECEIVE", Whitelisted::SendAndReceive),
                                         std::make_tuple("SEND", Whitelisted::Send),
                                         std::make_tuple("RECEIVE", Whitelisted::Receive),
                                         std::make_tuple("NO_FEES", Whitelisted::NoFees),
                                         std::make_tuple("ADDRESS", Whitelisted::Address)));
