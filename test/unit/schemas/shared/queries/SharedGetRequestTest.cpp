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
#include "enjinsdk/shared/GetRequest.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SharedGetRequestTest : public TransactionFragmentArgumentsTestSuite<GetRequest>,
                             public JsonTestSuite,
                             public testing::Test {
public:
    GetRequest class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1,"transactionId":"1"})";

    static GetRequest create_default_request() {
        GetRequest request = GetRequest()
                .set_id(1)
                .set_transaction_id("1");
        set_transaction_fragment_arguments(request);
        return request;
    }
};

TEST_F(SharedGetRequestTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetRequestTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id(1)
                    .set_transaction_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetRequestTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetRequest lhs;
    GetRequest rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetRequestTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetRequest lhs = create_default_request();
    GetRequest rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetRequestTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetRequest lhs = create_default_request();
    GetRequest rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedGetRequestTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetRequest lhs;
    GetRequest rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
