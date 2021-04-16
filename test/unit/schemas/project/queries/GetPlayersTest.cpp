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

#include "JsonTestSuite.hpp"
#include "PaginationArgumentsTestSuite.hpp"
#include "PlayerFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/project/GetPlayers.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class GetPlayersTest : public PlayerFragmentArgumentsTestSuite<GetPlayers>,
                       public PaginationArgumentsTestSuite<GetPlayers>,
                       public JsonTestSuite,
                       public testing::Test {
public:
    GetPlayers class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{}})";

    static GetPlayers create_default_request() {
        GetPlayers request = GetPlayers()
                .set_filter(PlayerFilter());
        set_player_fragment_arguments(request);
        set_pagination_arguments(request);
        return request;
    }
};

TEST_F(GetPlayersTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetPlayersTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_filter(PlayerFilter());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetPlayersTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetPlayers lhs;
    GetPlayers rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetPlayersTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetPlayers lhs = create_default_request();
    GetPlayers rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetPlayersTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetPlayers lhs = create_default_request();
    GetPlayers rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetPlayersTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetPlayers lhs;
    GetPlayers rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
