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
#include "enjinsdk/models/TransactionFilter.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class TransactionFilterTest : public JsonTestSuite,
                              public testing::Test {
public:
    TransactionFilter class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"and":[],"or":[],"id":"1","id_in":[],"transactionId":"1","transactionId_in":[],"assetId":"1","assetId_in":[],"type":"APPROVE","type_in":[],"value":1,"value_gt":1,"value_gte":1,"value_lt":1,"value_lte":1,"state":"PENDING","state_in":[],"wallet":"1","wallet_in":[]})";

    static TransactionFilter create_default_filter() {
        return TransactionFilter().set_and(std::vector<TransactionFilter>())
                                  .set_or(std::vector<TransactionFilter>())
                                  .set_id("1")
                                  .set_id_in(std::vector<std::string>())
                                  .set_transaction_id("1")
                                  .set_transaction_id_in(std::vector<std::string>())
                                  .set_asset_id("1")
                                  .set_asset_id_in(std::vector<std::string>())
                                  .set_type(RequestType::APPROVE)
                                  .set_type_in(std::vector<RequestType>())
                                  .set_value(1)
                                  .set_value_gt(1)
                                  .set_value_gte(1)
                                  .set_value_lt(1)
                                  .set_value_lte(1)
                                  .set_state(RequestState::PENDING)
                                  .set_state_in(std::vector<RequestState>())
                                  .set_wallet("1")
                                  .set_wallet_in(std::vector<std::string>());
    }
};

TEST_F(TransactionFilterTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionFilterTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_and(std::vector<TransactionFilter>())
                    .set_or(std::vector<TransactionFilter>())
                    .set_id("1")
                    .set_id_in(std::vector<std::string>())
                    .set_transaction_id("1")
                    .set_transaction_id_in(std::vector<std::string>())
                    .set_asset_id("1")
                    .set_asset_id_in(std::vector<std::string>())
                    .set_type(RequestType::APPROVE)
                    .set_type_in(std::vector<RequestType>())
                    .set_value(1)
                    .set_value_gt(1)
                    .set_value_gte(1)
                    .set_value_lt(1)
                    .set_value_lte(1)
                    .set_state(RequestState::PENDING)
                    .set_state_in(std::vector<RequestState>())
                    .set_wallet("1")
                    .set_wallet_in(std::vector<std::string>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionFilterTest, SerializeRequestInFieldSetReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(R"({"type_in":["APPROVE","APPROVE","APPROVE"]})");
    class_under_test.set_type_in({RequestType::APPROVE, RequestType::APPROVE, RequestType::APPROVE});

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionFilterTest, SerializeStateInReturnsFieldSetExpectedJsonObject) {
    // Arrange
    const std::string expected(R"({"state_in":["PENDING","PENDING","PENDING"]})");
    std::vector<RequestState> states;
    class_under_test.set_state_in({RequestState::PENDING, RequestState::PENDING, RequestState::PENDING});

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionFilterTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionFilter lhs;
    TransactionFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionFilterTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionFilter lhs = create_default_filter();
    TransactionFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionFilterTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionFilter lhs = create_default_filter();
    TransactionFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionFilterTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionFilter lhs;
    TransactionFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

