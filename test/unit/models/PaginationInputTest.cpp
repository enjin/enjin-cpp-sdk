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
#include "enjinsdk/models/PaginationInput.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class PaginationInputTest : public JsonTestSuite,
                            public testing::Test {
public:
    PaginationInput class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"page":1,"limit":1})";

    static PaginationInput create_default_pagination_options() {
        return PaginationInput().set_page(1)
                                .set_limit(1);
    }
};

TEST_F(PaginationInputTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationInputTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_page(1)
                    .set_limit(1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationInputTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PaginationInput lhs;
    PaginationInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationInputTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PaginationInput lhs = create_default_pagination_options();
    PaginationInput rhs = create_default_pagination_options();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationInputTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationInput lhs = create_default_pagination_options();
    PaginationInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PaginationInputTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationInput lhs;
    PaginationInput rhs = create_default_pagination_options();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
