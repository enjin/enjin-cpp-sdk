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

#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/internal/TransactionRequestArgumentsImpl.hpp"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class TransactionRequestArgumentsImplTest : public JsonTestSuite,
                                            public testing::Test {
public:
    TransactionRequestArgumentsImpl class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"send":true})";

    static TransactionRequestArgumentsImpl create_default_arguments() {
        TransactionRequestArgumentsImpl arguments;
        arguments.set_send(true);
        return arguments;
    }
};

TEST_F(TransactionRequestArgumentsImplTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionRequestArgumentsImplTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_send(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionRequestArgumentsImplTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionRequestArgumentsImpl lhs;
    TransactionRequestArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionRequestArgumentsImplTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionRequestArgumentsImpl lhs = create_default_arguments();
    TransactionRequestArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionRequestArgumentsImplTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionRequestArgumentsImpl lhs = create_default_arguments();
    TransactionRequestArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionRequestArgumentsImplTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionRequestArgumentsImpl lhs;
    TransactionRequestArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
