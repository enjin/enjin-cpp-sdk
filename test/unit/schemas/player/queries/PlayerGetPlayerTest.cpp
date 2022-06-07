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

#include "JsonTestSuite.hpp"
#include "PlayerFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/player/GetPlayer.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::player;
using namespace enjin::test::suites;

class PlayerGetPlayerTest : public PlayerFragmentArgumentsTestSuite<GetPlayer>,
                            public JsonTestSuite,
                            public testing::Test {
public:
    GetPlayer class_under_test;

    static GetPlayer create_default_request() {
        GetPlayer request;
        set_player_fragment_arguments(request);
        return request;
    }
};

TEST_F(PlayerGetPlayerTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerGetPlayerTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetPlayer lhs;
    GetPlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerGetPlayerTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetPlayer lhs = create_default_request();
    GetPlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerGetPlayerTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetPlayer lhs = create_default_request();
    GetPlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PlayerGetPlayerTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetPlayer lhs;
    GetPlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
