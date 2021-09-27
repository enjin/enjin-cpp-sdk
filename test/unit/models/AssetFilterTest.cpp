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
#include "enjinsdk/models/AssetFilter.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class AssetFilterTest : public JsonTestSuite,
                        public testing::Test {
public:
    AssetFilter class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"and":[],"or":[],"id":"1","id_in":[],"name":"1","name_contains":"1","name_in":[],"name_starts_with":"1","name_ends_with":"1","wallet":"1","wallet_in":[]})";

    static AssetFilter create_default_filter() {
        return AssetFilter().set_and(std::vector<AssetFilter>())
                            .set_or(std::vector<AssetFilter>())
                            .set_id("1")
                            .set_id_in(std::vector<std::string>())
                            .set_name("1")
                            .set_name_contains("1")
                            .set_name_in(std::vector<std::string>())
                            .set_name_starts_with("1")
                            .set_name_ends_with("1")
                            .set_wallet("1")
                            .set_wallet_in(std::vector<std::string>());
    }
};

TEST_F(AssetFilterTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetFilterTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_and(std::vector<AssetFilter>())
                    .set_or(std::vector<AssetFilter>())
                    .set_id("1")
                    .set_id_in(std::vector<std::string>())
                    .set_name("1")
                    .set_name_contains("1")
                    .set_name_in(std::vector<std::string>())
                    .set_name_starts_with("1")
                    .set_name_ends_with("1")
                    .set_wallet("1")
                    .set_wallet_in(std::vector<std::string>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetFilterTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AssetFilter lhs;
    AssetFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetFilterTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AssetFilter lhs = create_default_filter();
    AssetFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetFilterTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetFilter lhs = create_default_filter();
    AssetFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AssetFilterTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetFilter lhs;
    AssetFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
