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
#include "enjinsdk/project/SetApprovalForAll.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectSetApprovalForAllTest : public ProjectTransactionRequestArgumentsTestSuite<SetApprovalForAll>,
                                     public JsonTestSuite,
                                     public testing::Test {
public:
    SetApprovalForAll class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"operatorAddress":"1","approved":true})";

    static SetApprovalForAll create_default_request() {
        SetApprovalForAll request = SetApprovalForAll()
                .set_operator_address("1")
                .set_approved(true);
        set_project_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ProjectSetApprovalForAllTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectSetApprovalForAllTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_operator_address("1")
                    .set_approved(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectSetApprovalForAllTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SetApprovalForAll lhs;
    SetApprovalForAll rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectSetApprovalForAllTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SetApprovalForAll lhs = create_default_request();
    SetApprovalForAll rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectSetApprovalForAllTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SetApprovalForAll lhs = create_default_request();
    SetApprovalForAll rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectSetApprovalForAllTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SetApprovalForAll lhs;
    SetApprovalForAll rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
