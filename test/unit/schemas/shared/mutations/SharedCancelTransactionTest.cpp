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
#include "enjinsdk/shared/CancelTransaction.hpp"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SharedCancelTransactionTest : public JsonTestSuite,
                                    public testing::Test {
public:
    CancelTransaction class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1})";

    static CancelTransaction create_default_request() {
        return CancelTransaction().set_id(1);
    }
};

TEST_F(SharedCancelTransactionTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedCancelTransactionTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id(1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedCancelTransactionTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CancelTransaction lhs;
    CancelTransaction rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedCancelTransactionTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CancelTransaction lhs = create_default_request();
    CancelTransaction rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedCancelTransactionTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CancelTransaction lhs = create_default_request();
    CancelTransaction rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedCancelTransactionTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CancelTransaction lhs;
    CancelTransaction rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
