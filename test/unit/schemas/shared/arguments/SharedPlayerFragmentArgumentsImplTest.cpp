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
#include "enjinsdk/internal/PlayerFragmentArgumentsImpl.hpp"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SharedPlayerFragmentArgumentsImplTest : public JsonTestSuite,
                                              public testing::Test {
public:
    PlayerFragmentArgumentsImpl class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"withLinkingInfo":true,"linkingCodeQrSize":1,"withPlayerWallet":true})";

    static PlayerFragmentArgumentsImpl create_default_arguments() {
        PlayerFragmentArgumentsImpl arguments;
        arguments.set_with_linking_info();
        arguments.set_qr_size(1);
        arguments.set_with_wallet();
        return arguments;
    }
};

TEST_F(SharedPlayerFragmentArgumentsImplTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsImplTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_with_linking_info();
    class_under_test.set_qr_size(1);
    class_under_test.set_with_wallet();

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedPlayerFragmentArgumentsImplTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PlayerFragmentArgumentsImpl lhs;
    PlayerFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPlayerFragmentArgumentsImplTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PlayerFragmentArgumentsImpl lhs = create_default_arguments();
    PlayerFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedPlayerFragmentArgumentsImplTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PlayerFragmentArgumentsImpl lhs = create_default_arguments();
    PlayerFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedPlayerFragmentArgumentsImplTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PlayerFragmentArgumentsImpl lhs;
    PlayerFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
