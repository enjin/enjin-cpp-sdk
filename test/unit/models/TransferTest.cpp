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
#include "enjinsdk/models/Transfer.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class TransferTest : public JsonTestSuite,
                     public testing::Test {
public:
    Transfer class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"from":"1","to":"1","assetId":"1","assetIndex":"1","value":"1"})";

    static Transfer create_default_transfer() {
        return Transfer().set_from("1")
                         .set_to("1")
                         .set_asset_id("1")
                         .set_asset_index("1")
                         .set_value("1");
    }
};

TEST_F(TransferTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransferTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_from("1")
                    .set_to("1")
                    .set_asset_id("1")
                    .set_asset_index("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransferTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Transfer lhs;
    Transfer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransferTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Transfer lhs = create_default_transfer();
    Transfer rhs = create_default_transfer();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransferTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Transfer lhs = create_default_transfer();
    Transfer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransferTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Transfer lhs;
    Transfer rhs = create_default_transfer();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
