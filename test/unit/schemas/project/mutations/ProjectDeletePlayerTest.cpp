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

#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/project/DeletePlayer.hpp"
#include <string>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectDeletePlayerTest : public JsonTestSuite,
                                public testing::Test {
public:
    DeletePlayer class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static DeletePlayer create_default_request() {
        return DeletePlayer().set_id("1");
    }
};

TEST_F(ProjectDeletePlayerTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectDeletePlayerTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectDeletePlayerTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    DeletePlayer lhs;
    DeletePlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectDeletePlayerTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    DeletePlayer lhs = create_default_request();
    DeletePlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectDeletePlayerTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    DeletePlayer lhs = create_default_request();
    DeletePlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectDeletePlayerTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    DeletePlayer lhs;
    DeletePlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
