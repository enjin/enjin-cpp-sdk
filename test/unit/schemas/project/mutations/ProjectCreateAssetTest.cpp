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
#include "enjinsdk/project/CreateAsset.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectCreateAssetTest : public ProjectTransactionRequestArgumentsTestSuite<CreateAsset>,
                               public JsonTestSuite,
                               public testing::Test {
public:
    CreateAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"name":"1","totalSupply":"1","initialReserve":"1","supplyModel":"FIXED","meltValue":"1","meltFeeRatio":1,"transferable":"PERMANENT","transferFeeSettings":{},"nonFungible":true})";

    static CreateAsset create_default_request() {
        CreateAsset request = CreateAsset()
                .set_name("1")
                .set_total_supply("1")
                .set_initial_reserve("1")
                .set_supply_model(AssetSupplyModel::Fixed)
                .set_melt_value("1")
                .set_melt_fee_ratio(1)
                .set_transferable(AssetTransferable::Permanent)
                .set_transfer_fee_settings(AssetTransferFeeSettingsInput())
                .set_non_fungible(true);
        set_project_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ProjectCreateAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectCreateAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_name("1")
                    .set_total_supply("1")
                    .set_initial_reserve("1")
                    .set_supply_model(AssetSupplyModel::Fixed)
                    .set_melt_value("1")
                    .set_melt_fee_ratio(1)
                    .set_transferable(AssetTransferable::Permanent)
                    .set_transfer_fee_settings(AssetTransferFeeSettingsInput())
                    .set_non_fungible(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectCreateAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CreateAsset lhs;
    CreateAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectCreateAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CreateAsset lhs = create_default_request();
    CreateAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectCreateAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateAsset lhs = create_default_request();
    CreateAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectCreateAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateAsset lhs;
    CreateAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
