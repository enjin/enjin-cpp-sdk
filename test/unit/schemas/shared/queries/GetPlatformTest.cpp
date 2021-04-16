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
#include "enjinsdk/shared/GetPlatform.hpp"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class GetPlatformTest : public JsonTestSuite,
                        public testing::Test {
public:
    GetPlatform class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"withContracts":true,"withNotificationDrivers":true})";

    static GetPlatform create_default_request() {
        return GetPlatform().set_with_contracts()
                            .set_with_notifications();
    }
};

TEST_F(GetPlatformTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetPlatformTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_with_contracts()
                    .set_with_notifications();

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetPlatformTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetPlatform lhs;
    GetPlatform rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetPlatformTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetPlatform lhs = create_default_request();
    GetPlatform rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetPlatformTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetPlatform lhs = create_default_request();
    GetPlatform rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetPlatformTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetPlatform lhs;
    GetPlatform rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
