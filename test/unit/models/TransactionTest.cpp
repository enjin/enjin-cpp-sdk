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
#include "enjinsdk/models/Transaction.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class TransactionTest : public JsonTestSuite,
                        public testing::Test {
public:
    Transaction class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1,"transactionId":"1","title":"1","contract":"1","type":"APPROVE","value":"1","retryState":"1","state":"PENDING","accepted":true,"projectWallet":true,"blockchainData":{},"project":{},"asset":{},"wallet":{},"createdAt":"1","updatedAt":"1"})";
};

TEST_F(TransactionTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_transaction_id().has_value());
    EXPECT_FALSE(class_under_test.get_title().has_value());
    EXPECT_FALSE(class_under_test.get_contract().has_value());
    EXPECT_FALSE(class_under_test.get_type().has_value());
    EXPECT_FALSE(class_under_test.get_value().has_value());
    EXPECT_FALSE(class_under_test.get_retry_state().has_value());
    EXPECT_FALSE(class_under_test.get_state().has_value());
    EXPECT_FALSE(class_under_test.get_accepted().has_value());
    EXPECT_FALSE(class_under_test.get_project_wallet().has_value());
    EXPECT_FALSE(class_under_test.get_blockchain_data().has_value());
    EXPECT_FALSE(class_under_test.get_project().has_value());
    EXPECT_FALSE(class_under_test.get_asset().has_value());
    EXPECT_FALSE(class_under_test.get_wallet().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(TransactionTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EmptyJsonObject);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_transaction_id().has_value());
    EXPECT_FALSE(class_under_test.get_title().has_value());
    EXPECT_FALSE(class_under_test.get_contract().has_value());
    EXPECT_FALSE(class_under_test.get_type().has_value());
    EXPECT_FALSE(class_under_test.get_value().has_value());
    EXPECT_FALSE(class_under_test.get_retry_state().has_value());
    EXPECT_FALSE(class_under_test.get_state().has_value());
    EXPECT_FALSE(class_under_test.get_accepted().has_value());
    EXPECT_FALSE(class_under_test.get_project_wallet().has_value());
    EXPECT_FALSE(class_under_test.get_blockchain_data().has_value());
    EXPECT_FALSE(class_under_test.get_project().has_value());
    EXPECT_FALSE(class_under_test.get_asset().has_value());
    EXPECT_FALSE(class_under_test.get_wallet().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(TransactionTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const int expected_int = 1;
    const bool expected_bool = true;
    const std::string expected_string("1");
    const TransactionState expected_request_state = TransactionState::Pending;
    const TransactionType expected_request_type = TransactionType::Approve;
    const BlockchainData expected_blockchain_data;
    const Project expected_project;
    const Asset expected_asset;
    const Wallet expected_wallet;

    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_int, class_under_test.get_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_transaction_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_title().value());
    EXPECT_EQ(expected_string, class_under_test.get_contract().value());
    EXPECT_EQ(expected_request_type, class_under_test.get_type().value());
    EXPECT_EQ(expected_string, class_under_test.get_value().value());
    EXPECT_EQ(expected_string, class_under_test.get_retry_state().value());
    EXPECT_EQ(expected_request_state, class_under_test.get_state().value());
    EXPECT_EQ(expected_bool, class_under_test.get_accepted().value());
    EXPECT_EQ(expected_bool, class_under_test.get_project_wallet().value());
    EXPECT_EQ(expected_blockchain_data, class_under_test.get_blockchain_data().value());
    EXPECT_EQ(expected_project, class_under_test.get_project().value());
    EXPECT_EQ(expected_asset, class_under_test.get_asset().value());
    EXPECT_EQ(expected_wallet, class_under_test.get_wallet().value());
    EXPECT_EQ(expected_string, class_under_test.get_created_at().value());
    EXPECT_EQ(expected_string, class_under_test.get_updated_at().value());
}

TEST_F(TransactionTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Transaction lhs;
    Transaction rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Transaction lhs;
    Transaction rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Transaction lhs;
    Transaction rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Transaction lhs;
    Transaction rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionTest, CopyOperatorCopyEqualsOriginal) {
    // Arrange
    Transaction original;
    Transaction copy;
    original.deserialize(POPULATED_JSON_OBJECT);

    // Act
    copy = original;

    // Assert
    ASSERT_EQ(original, copy);
}
