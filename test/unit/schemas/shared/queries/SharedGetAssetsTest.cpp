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
#include "PaginationArgumentsTestSuite.hpp"
#include "enjinsdk/shared/GetAssets.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SharedGetAssetsTest : public AssetFragmentArgumentsTestSuite<GetAssets>,
                            public PaginationArgumentsTestSuite<GetAssets>,
                            public JsonTestSuite,
                            public testing::Test {
public:
    GetAssets class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{},"sort":{}})";

    static GetAssets create_default_request() {
        GetAssets request = GetAssets()
                .set_filter(AssetFilter())
                .set_sort(AssetSortInput());
        set_asset_fragment_arguments(request);
        set_pagination_arguments(request);
        return request;
    }
};

TEST_F(SharedGetAssetsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetAssetsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_filter(AssetFilter())
                    .set_sort(AssetSortInput());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedGetAssetsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetAssets lhs;
    GetAssets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetAssetsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetAssets lhs = create_default_request();
    GetAssets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedGetAssetsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAssets lhs = create_default_request();
    GetAssets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedGetAssetsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAssets lhs;
    GetAssets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
