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
#include "enjinsdk/internal/ProjectTransactionRequestArgumentsImpl.hpp"
#include <string>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectTransactionRequestArgumentsImplTest : public JsonTestSuite,
                                                   public testing::Test {
public:
    ProjectTransactionRequestArgumentsImpl class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"ethAddress":"1"})";

    static ProjectTransactionRequestArgumentsImpl create_default_arguments() {
        ProjectTransactionRequestArgumentsImpl arguments;
        arguments.set_eth_address("1");
        return arguments;
    }
};

TEST_F(ProjectTransactionRequestArgumentsImplTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectTransactionRequestArgumentsImplTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_eth_address("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectTransactionRequestArgumentsImplTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    ProjectTransactionRequestArgumentsImpl lhs;
    ProjectTransactionRequestArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectTransactionRequestArgumentsImplTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    ProjectTransactionRequestArgumentsImpl lhs = create_default_arguments();
    ProjectTransactionRequestArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectTransactionRequestArgumentsImplTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    ProjectTransactionRequestArgumentsImpl lhs = create_default_arguments();
    ProjectTransactionRequestArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectTransactionRequestArgumentsImplTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    ProjectTransactionRequestArgumentsImpl lhs;
    ProjectTransactionRequestArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
