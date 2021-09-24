/* Copyright 2021 Enjin Pte Ltd.
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

using namespace enjin::sdk::utils;
using namespace enjin::pusher;

class PusherConnectionStateTest : public testing::TestWithParam<std::tuple<std::string, PusherConnectionState>> {
};

TEST_P(PusherConnectionStateTest, SerializeConnectionStateReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    PusherConnectionState value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_pusher_connection_state(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializePusherConnectionState,
                         PusherConnectionStateTest,
                         testing::Values(std::make_tuple("ALL", PusherConnectionState::ALL),
                                         std::make_tuple("CONNECTED", PusherConnectionState::CONNECTED),
                                         std::make_tuple("CONNECTING", PusherConnectionState::CONNECTING),
                                         std::make_tuple("DISCONNECTED", PusherConnectionState::DISCONNECTED),
                                         std::make_tuple("DISCONNECTING", PusherConnectionState::DISCONNECTING),
                                         std::make_tuple("RECONNECTING", PusherConnectionState::RECONNECTING)));
