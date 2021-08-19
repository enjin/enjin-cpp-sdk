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

#include "JsonTestSuite.hpp"
#include "ProjectTransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/project/SendAsset.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class SendAssetTest : public ProjectTransactionRequestArgumentsTestSuite<SendAsset>,
                      public JsonTestSuite,
                      public testing::Test {
public:
    SendAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"recipientAddress":"1","assetId":"1","assetIndex":"1","value":"1","data":"1"})";

    static SendAsset create_default_request() {
        SendAsset request = SendAsset()
                .set_recipient_address("1")
                .set_asset_id("1")
                .set_asset_index("1")
                .set_value("1")
                .set_data("1");
        set_project_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(SendAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SendAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_recipient_address("1")
                    .set_asset_id("1")
                    .set_asset_index("1")
                    .set_value("1")
                    .set_data("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SendAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SendAsset lhs;
    SendAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SendAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SendAsset lhs = create_default_request();
    SendAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SendAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SendAsset lhs = create_default_request();
    SendAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SendAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SendAsset lhs;
    SendAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
