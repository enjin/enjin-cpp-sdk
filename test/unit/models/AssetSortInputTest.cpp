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
#include "enjinsdk/models/AssetSortInput.hpp"

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class AssetSortInputTest : public JsonTestSuite,
                           public testing::Test {
public:
    AssetSortInput class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"field":"id","direction":"asc"})";

    static AssetSortInput create_default_sort() {
        return AssetSortInput().set_field(AssetField::Id)
                               .set_direction(SortDirection::Ascending);
    }
};

TEST_F(AssetSortInputTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetSortInputTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_field(AssetField::Id)
                    .set_direction(SortDirection::Ascending);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetSortInputTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AssetSortInput lhs;
    AssetSortInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetSortInputTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AssetSortInput lhs = create_default_sort();
    AssetSortInput rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetSortInputTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetSortInput lhs = create_default_sort();
    AssetSortInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AssetSortInputTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetSortInput lhs;
    AssetSortInput rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
