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
#include "TransactionFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/player/ApproveMaxEnj.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::player;
using namespace enjin::test::suites;

class PlayerApproveMaxEnjTest : public TransactionFragmentArgumentsTestSuite<ApproveMaxEnj>,
                                public JsonTestSuite,
                                public testing::Test {
public:
    static ApproveMaxEnj create_default_request() {
        ApproveMaxEnj request;
        set_transaction_fragment_arguments(request);
        return request;
    }
};

TEST_F(PlayerApproveMaxEnjTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    ApproveMaxEnj lhs;
    ApproveMaxEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerApproveMaxEnjTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    ApproveMaxEnj lhs = create_default_request();
    ApproveMaxEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerApproveMaxEnjTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    ApproveMaxEnj lhs = create_default_request();
    ApproveMaxEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PlayerApproveMaxEnjTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    ApproveMaxEnj lhs;
    ApproveMaxEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
