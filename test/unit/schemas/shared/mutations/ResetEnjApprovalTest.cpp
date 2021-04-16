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
#include "TransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/shared/ResetEnjApproval.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class ResetEnjApprovalTest : public TransactionRequestArgumentsTestSuite<ResetEnjApproval>,
                             public JsonTestSuite,
                             public testing::Test {
public:
    static ResetEnjApproval create_default_request() {
        ResetEnjApproval request;
        set_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ResetEnjApprovalTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    ResetEnjApproval lhs;
    ResetEnjApproval rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ResetEnjApprovalTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    ResetEnjApproval lhs = create_default_request();
    ResetEnjApproval rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ResetEnjApprovalTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    ResetEnjApproval lhs = create_default_request();
    ResetEnjApproval rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ResetEnjApprovalTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    ResetEnjApproval lhs;
    ResetEnjApproval rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
