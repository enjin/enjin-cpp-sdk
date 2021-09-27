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

#include "JsonTestSuite.hpp"
#include "ProjectTransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/project/ApproveMaxEnj.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectApproveMaxEnjTest : public ProjectTransactionRequestArgumentsTestSuite<ApproveMaxEnj>,
                                 public JsonTestSuite,
                                 public testing::Test {
public:
    static ApproveMaxEnj create_default_request() {
        ApproveMaxEnj request;
        set_project_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ProjectApproveMaxEnjTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    ApproveMaxEnj lhs;
    ApproveMaxEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectApproveMaxEnjTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    ApproveMaxEnj lhs = create_default_request();
    ApproveMaxEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectApproveMaxEnjTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    ApproveMaxEnj lhs = create_default_request();
    ApproveMaxEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectApproveMaxEnjTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    ApproveMaxEnj lhs;
    ApproveMaxEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
