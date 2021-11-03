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
#include "ProjectTransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/project/BridgeClaimAsset.hpp"
#include <string>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectBridgeClaimAssetTest : public ProjectTransactionRequestArgumentsTestSuite<BridgeClaimAsset>,
                                    public JsonTestSuite,
                                    public ::testing::Test {
public:
    BridgeClaimAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1"})";

    static BridgeClaimAsset create_default_request() {
        BridgeClaimAsset request = BridgeClaimAsset()
                .set_asset_id("1");
        set_project_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ProjectBridgeClaimAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectBridgeClaimAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectBridgeClaimAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    BridgeClaimAsset lhs;
    BridgeClaimAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectBridgeClaimAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    BridgeClaimAsset lhs = create_default_request();
    BridgeClaimAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectBridgeClaimAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    BridgeClaimAsset lhs = create_default_request();
    BridgeClaimAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectBridgeClaimAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    BridgeClaimAsset lhs;
    BridgeClaimAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
