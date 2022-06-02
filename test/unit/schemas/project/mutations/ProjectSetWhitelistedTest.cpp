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
#include "enjinsdk/project/SetWhitelisted.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectSetWhitelistedTest : public ProjectTransactionRequestArgumentsTestSuite<SetWhitelisted>,
                                  public JsonTestSuite,
                                  public testing::Test {
public:
    SetWhitelisted class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","accountAddress":"1","whitelisted":"NONE","whitelistedAddress":"1","on":true})";

    static SetWhitelisted create_default_request() {
        SetWhitelisted request = SetWhitelisted()
                .set_asset_id("1")
                .set_account_address("1")
                .set_whitelisted(Whitelisted::None)
                .set_whitelisted_address("1")
                .set_on(true);
        set_project_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ProjectSetWhitelistedTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectSetWhitelistedTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_account_address("1")
                    .set_whitelisted(Whitelisted::None)
                    .set_whitelisted_address("1")
                    .set_on(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectSetWhitelistedTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SetWhitelisted lhs;
    SetWhitelisted rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectSetWhitelistedTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SetWhitelisted lhs = create_default_request();
    SetWhitelisted rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectSetWhitelistedTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SetWhitelisted lhs = create_default_request();
    SetWhitelisted rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectSetWhitelistedTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SetWhitelisted lhs;
    SetWhitelisted rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
