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
#include "enjinsdk/project/SetTransferable.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectSetTransferableTest : public ProjectTransactionRequestArgumentsTestSuite<SetTransferable>,
                                   public JsonTestSuite,
                                   public testing::Test {
public:
    SetTransferable class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","assetIndex":"1","transferable":"PERMANENT"})";

    static SetTransferable create_default_request() {
        SetTransferable request = SetTransferable()
                .set_asset_id("1")
                .set_asset_index("1")
                .set_transferable(AssetTransferable::PERMANENT);
        set_project_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ProjectSetTransferableTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectSetTransferableTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_asset_index("1")
                    .set_transferable(AssetTransferable::PERMANENT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectSetTransferableTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SetTransferable lhs;
    SetTransferable rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectSetTransferableTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SetTransferable lhs = create_default_request();
    SetTransferable rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectSetTransferableTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SetTransferable lhs = create_default_request();
    SetTransferable rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectSetTransferableTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SetTransferable lhs;
    SetTransferable rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
