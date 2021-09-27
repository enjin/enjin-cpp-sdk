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
#include "AssetFragmentArgumentsTestSuite.hpp"
#include "JsonTestSuite.hpp"
#include "enjinsdk/shared/GetAsset.hpp"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SharedGetAssetTest : public AssetFragmentArgumentsTestSuite<GetAsset>,
                           public JsonTestSuite,
                           public testing::Test {
public:
    GetAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static GetAsset create_default_request() {
        GetAsset request = GetAsset().set_id("1");
        set_asset_fragment_arguments(request);
        return request;
    }
};

TEST_F(SharedGetAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetAsset lhs;
    GetAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetAsset lhs = create_default_request();
    GetAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAsset lhs = create_default_request();
    GetAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedGetAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAsset lhs;
    GetAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
