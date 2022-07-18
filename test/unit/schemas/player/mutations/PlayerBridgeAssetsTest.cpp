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
#include "TransactionFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/player/BridgeAssets.hpp"
#include <string>

using namespace enjin::sdk::player;
using namespace enjin::test::suites;

class PlayerBridgeAssetsTest : public TransactionFragmentArgumentsTestSuite<BridgeAssets>,
                               public JsonTestSuite,
                               public ::testing::Test {
public:
    BridgeAssets class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","assetIndices":["1","1","1"]})";

    static BridgeAssets create_default_request() {
        BridgeAssets request = BridgeAssets()
                .set_asset_id("1")
                .set_asset_indices({"1", "1", "1"});
        set_transaction_fragment_arguments(request);
        return request;
    }
};

TEST_F(PlayerBridgeAssetsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerBridgeAssetsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_asset_indices({"1", "1", "1"});

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerBridgeAssetsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    BridgeAssets lhs;
    BridgeAssets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerBridgeAssetsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    BridgeAssets lhs = create_default_request();
    BridgeAssets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerBridgeAssetsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    BridgeAssets lhs = create_default_request();
    BridgeAssets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PlayerBridgeAssetsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    BridgeAssets lhs;
    BridgeAssets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
