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
#include "JsonTestSuite.hpp"
#include "enjinsdk/models/PlayerFilter.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class PlayerFilterTest : public JsonTestSuite,
                         public testing::Test {
public:
    PlayerFilter class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"and":[],"or":[],"id":"1","id_in":[]})";

    static PlayerFilter create_default_filter() {
        return PlayerFilter().set_and(std::vector<PlayerFilter>())
                             .set_or(std::vector<PlayerFilter>())
                             .set_id("1")
                             .set_id_in(std::vector<std::string>());
    }
};

TEST_F(PlayerFilterTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerFilterTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_and(std::vector<PlayerFilter>())
                    .set_or(std::vector<PlayerFilter>())
                    .set_id("1")
                    .set_id_in(std::vector<std::string>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerFilterTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PlayerFilter lhs;
    PlayerFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerFilterTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PlayerFilter lhs = create_default_filter();
    PlayerFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerFilterTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PlayerFilter lhs = create_default_filter();
    PlayerFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PlayerFilterTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PlayerFilter lhs;
    PlayerFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
