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
#include "PaginationArgumentsTestSuite.hpp"
#include "TransactionFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/shared/GetRequests.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SharedGetRequestsTest : public TransactionFragmentArgumentsTestSuite<GetRequests>,
                              public PaginationArgumentsTestSuite<GetRequests>,
                              public JsonTestSuite,
                              public testing::Test {
public:
    GetRequests class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{},"sort":{}})";

    static GetRequests create_default_request() {
        GetRequests requests = GetRequests()
                .set_filter(TransactionFilter())
                .set_sort(TransactionSort());
        set_transaction_fragment_arguments(requests);
        set_pagination_arguments(requests);
        return requests;
    }
};

TEST_F(SharedGetRequestsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetRequestsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_filter(TransactionFilter())
                    .set_sort(TransactionSort());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetRequestsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetRequests lhs;
    GetRequests rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetRequestsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetRequests lhs = create_default_request();
    GetRequests rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetRequestsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetRequests lhs = create_default_request();
    GetRequests rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedGetRequestsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetRequests lhs;
    GetRequests rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
