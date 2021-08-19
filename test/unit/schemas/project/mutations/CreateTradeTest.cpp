/* Copyright 2021 Enjin Pte Ltd.
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

#include "JsonTestSuite.hpp"
#include "ProjectTransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/project/CreateTrade.hpp"
#include "gtest/gtest.h"
#include <string>
#include <vector>

using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class CreateTradeTest : public ProjectTransactionRequestArgumentsTestSuite<CreateTrade>,
                        public JsonTestSuite,
                        public testing::Test {
public:
    CreateTrade class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"askingAssets":[],"offeringAssets":[],"recipientAddress":"1"})";

    static CreateTrade create_default_request() {
        CreateTrade request = CreateTrade()
                .set_asking_assets(std::vector<Trade>())
                .set_offering_assets(std::vector<Trade>())
                .set_recipient_address("1");
        set_project_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(CreateTradeTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreateTradeTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asking_assets(std::vector<Trade>())
                    .set_offering_assets(std::vector<Trade>())
                    .set_recipient_address("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreateTradeTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CreateTrade lhs;
    CreateTrade rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateTradeTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CreateTrade lhs = create_default_request();
    CreateTrade rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateTradeTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateTrade lhs = create_default_request();
    CreateTrade rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(CreateTradeTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateTrade lhs;
    CreateTrade rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
