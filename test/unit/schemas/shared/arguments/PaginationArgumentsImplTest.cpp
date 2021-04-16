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
#include "enjinsdk/internal/PaginationArgumentsImpl.hpp"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class PaginationArgumentsImplTest : public JsonTestSuite,
                                    public testing::Test {
public:
    PaginationArgumentsImpl class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"pagination":{"page":1,"limit":1}})";

    static PaginationArgumentsImpl create_default_arguments() {
        PaginationArgumentsImpl arguments;
        arguments.set_pagination(1, 1);
        return arguments;
    }
};

TEST_F(PaginationArgumentsImplTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationArgumentsImplTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_pagination(1, 1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationArgumentsImplTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PaginationArgumentsImpl lhs;
    PaginationArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationArgumentsImplTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PaginationArgumentsImpl lhs = create_default_arguments();
    PaginationArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationArgumentsImplTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationArgumentsImpl lhs = create_default_arguments();
    PaginationArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PaginationArgumentsImplTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationArgumentsImpl lhs;
    PaginationArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
