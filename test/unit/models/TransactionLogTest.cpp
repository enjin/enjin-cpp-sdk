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
#include "enjinsdk/models/TransactionLog.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class TransactionLogTest : public JsonTestSuite,
                           public testing::Test {
public:
    TransactionLog class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"blockNumber":1,"address":"1","transactionHash":"1","data":[],"topics":[],"event":{}})";
};

TEST_F(TransactionLogTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_block_number().has_value());
    EXPECT_FALSE(class_under_test.get_address().has_value());
    EXPECT_FALSE(class_under_test.get_transaction_hash().has_value());
    EXPECT_FALSE(class_under_test.get_data().has_value());
    EXPECT_FALSE(class_under_test.get_topics().has_value());
    EXPECT_FALSE(class_under_test.get_event().has_value());
}

TEST_F(TransactionLogTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EmptyJsonObject);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_block_number().has_value());
    EXPECT_FALSE(class_under_test.get_address().has_value());
    EXPECT_FALSE(class_under_test.get_transaction_hash().has_value());
    EXPECT_FALSE(class_under_test.get_data().has_value());
    EXPECT_FALSE(class_under_test.get_topics().has_value());
    EXPECT_FALSE(class_under_test.get_event().has_value());
}

TEST_F(TransactionLogTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const int expected_int = 1;
    const std::string expected_string("1");
    const TransactionEvent expected_event;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_int, class_under_test.get_block_number().value());
    EXPECT_EQ(expected_string, class_under_test.get_address().value());
    EXPECT_EQ(expected_string, class_under_test.get_transaction_hash().value());
    EXPECT_TRUE(class_under_test.get_data().has_value());
    EXPECT_TRUE(class_under_test.get_topics().has_value());
    EXPECT_EQ(expected_event, class_under_test.get_event().value());
}

TEST_F(TransactionLogTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionLog lhs;
    TransactionLog rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionLogTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionLog lhs;
    TransactionLog rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionLogTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionLog lhs;
    TransactionLog rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionLogTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionLog lhs;
    TransactionLog rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
