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
#include "enjinsdk/models/Melt.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class MeltTest : public JsonTestSuite,
                 public testing::Test {
public:
    Melt class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","assetIndex":"1","value":"1"})";

    static Melt create_default_melt() {
        return Melt().set_asset_id("1")
                     .set_asset_index("1")
                     .set_value("1");
    }
};

TEST_F(MeltTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MeltTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_asset_index("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MeltTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Melt lhs;
    Melt rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MeltTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Melt lhs = create_default_melt();
    Melt rhs = create_default_melt();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MeltTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Melt lhs = create_default_melt();
    Melt rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(MeltTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Melt lhs;
    Melt rhs = create_default_melt();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
