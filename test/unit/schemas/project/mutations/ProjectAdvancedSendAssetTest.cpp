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
#include "enjinsdk/project/AdvancedSendAsset.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectAdvancedSendAssetTest : public ProjectTransactionRequestArgumentsTestSuite<AdvancedSendAsset>,
                                     public JsonTestSuite,
                                     public testing::Test {
public:
    AdvancedSendAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"transfers":[],"data":"1"})";

    static AdvancedSendAsset create_default_request() {
        AdvancedSendAsset request = AdvancedSendAsset()
                .set_transfers(std::vector<Transfer>())
                .set_data("1");
        set_project_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ProjectAdvancedSendAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectAdvancedSendAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_transfers(std::vector<Transfer>())
                    .set_data("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectAdvancedSendAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AdvancedSendAsset lhs;
    AdvancedSendAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectAdvancedSendAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AdvancedSendAsset lhs = create_default_request();
    AdvancedSendAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectAdvancedSendAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AdvancedSendAsset lhs = create_default_request();
    AdvancedSendAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectAdvancedSendAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AdvancedSendAsset lhs;
    AdvancedSendAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
