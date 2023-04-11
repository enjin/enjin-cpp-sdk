/* Copyright 2023 Enjin Pte. Ltd.
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
#include "enjinsdk/project/GetAssetsFromProjects.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class ProjectGetAssetsFromProjectsTest : public AssetFragmentArgumentsTestSuite<GetAssetsFromProjects>,
                                         public PaginationArgumentsTestSuite<GetAssetsFromProjects>,
                                         public JsonTestSuite,
                                         public testing::Test {
public:
    GetAssetsFromProjects class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"projects":["1"],"filter":{},"sort":{}})";

    static GetAssetsFromProjects create_default_request() {
        GetAssetsFromProjects request = GetAssetsFromProjects()
                .set_projects({"1"})
                .set_filter(AssetFilter())
                .set_sort(AssetSortInput());
        set_asset_fragment_arguments(request);
        set_pagination_arguments(request);
        return request;
    }
};

TEST_F(ProjectGetAssetsFromProjectsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectGetAssetsFromProjectsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_projects({"1"})
                    .set_filter(AssetFilter())
                    .set_sort(AssetSortInput());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ProjectGetAssetsFromProjectsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetAssetsFromProjects lhs;
    GetAssetsFromProjects rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectGetAssetsFromProjectsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetAssetsFromProjects lhs = create_default_request();
    GetAssetsFromProjects rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ProjectGetAssetsFromProjectsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAssetsFromProjects lhs = create_default_request();
    GetAssetsFromProjects rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ProjectGetAssetsFromProjectsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAssetsFromProjects lhs;
    GetAssetsFromProjects rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
