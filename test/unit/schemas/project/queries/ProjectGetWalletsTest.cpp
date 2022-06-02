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
#include "WalletFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/project/GetWallets.hpp"
#include "gtest/gtest.h"
#include <string>
#include <vector>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectGetWalletsTest : public WalletFragmentArgumentsTestSuite<GetWallets>,
                              public JsonTestSuite,
                              public testing::Test {
public:
    GetWallets class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"userIds":[],"ethAddresses":[]})";

    static GetWallets create_default_request() {
        GetWallets request = GetWallets()
                .set_user_ids(std::vector<std::string>())
                .set_eth_addresses(std::vector<std::string>());
        set_wallet_fragment_arguments(request);
        return request;
    }
};

TEST_F(ProjectGetWalletsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectGetWalletsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_user_ids(std::vector<std::string>())
                    .set_eth_addresses(std::vector<std::string>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectGetWalletsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetWallets lhs;
    GetWallets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectGetWalletsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetWallets lhs = create_default_request();
    GetWallets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectGetWalletsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetWallets lhs = create_default_request();
    GetWallets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectGetWalletsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetWallets lhs;
    GetWallets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
