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
#include "BalanceFragmentArgumentsTestSuite.hpp"
#include "JsonTestSuite.hpp"
#include "PaginationArgumentsTestSuite.hpp"
#include "enjinsdk/shared/GetBalances.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SharedGetBalancesTest : public BalanceFragmentArgumentsTestSuite<GetBalances>,
                              public PaginationArgumentsTestSuite<GetBalances>,
                              public JsonTestSuite,
                              public testing::Test {
public:
    GetBalances class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{}})";

    static GetBalances create_default_request() {
        GetBalances request = GetBalances()
                .set_filter(BalanceFilter());
        set_balance_fragment_arguments(request);
        set_pagination_arguments(request);
        return request;
    }
};

TEST_F(SharedGetBalancesTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetBalancesTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_filter(BalanceFilter());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetBalancesTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetBalances lhs;
    GetBalances rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetBalancesTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetBalances lhs = create_default_request();
    GetBalances rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetBalancesTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetBalances lhs = create_default_request();
    GetBalances rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedGetBalancesTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetBalances lhs;
    GetBalances rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
