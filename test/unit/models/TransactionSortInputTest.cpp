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
#include "enjinsdk/models/TransactionSortInput.hpp"

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class TransactionSortInputTest : public JsonTestSuite,
                                 public testing::Test {
public:
    TransactionSortInput class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"field":"id","direction":"asc"})";

    static TransactionSortInput create_default_sort() {
        return TransactionSortInput().set_field(TransactionField::Id)
                                     .set_direction(SortDirection::Ascending);
    }
};

TEST_F(TransactionSortInputTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionSortInputTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_field(TransactionField::Id)
                    .set_direction(SortDirection::Ascending);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionSortInputTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionSortInput lhs;
    TransactionSortInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionSortInputTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionSortInput lhs = create_default_sort();
    TransactionSortInput rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionSortInputTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionSortInput lhs = create_default_sort();
    TransactionSortInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionSortInputTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionSortInput lhs;
    TransactionSortInput rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
