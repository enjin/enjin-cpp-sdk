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
#include "enjinsdk/models/TransactionSort.hpp"

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class TransactionSortTest : public JsonTestSuite,
                            public testing::Test {
public:
    TransactionSort class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"field":"id","direction":"asc"})";

    static TransactionSort create_default_sort() {
        return TransactionSort().set_field(TransactionField::ID)
                                .set_direction(SortDirection::ASCENDING);
    }
};

TEST_F(TransactionSortTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionSortTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_field(TransactionField::ID)
                    .set_direction(SortDirection::ASCENDING);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionSortTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionSort lhs;
    TransactionSort rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionSortTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionSort lhs = create_default_sort();
    TransactionSort rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionSortTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionSort lhs = create_default_sort();
    TransactionSort rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionSortTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionSort lhs;
    TransactionSort rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
