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
#include "TestableSharedAssetFragmentArguments.hpp"
#include <string>

using namespace enjin::sdk::json;
using namespace enjin::test::suites;
using namespace enjin::test::utils;

class SharedAssetFragmentArgumentsTest : public AssetFragmentArgumentsTestSuite<TestableSharedAssetFragmentArguments>,
                                         public JsonTestSuite,
                                         public testing::Test {
public:
    TestableSharedAssetFragmentArguments class_under_test;

    static TestableSharedAssetFragmentArguments create_default_arguments() {
        TestableSharedAssetFragmentArguments arguments;
        set_asset_fragment_arguments(arguments);
        return arguments;
    }
};

TEST_F(SharedAssetFragmentArgumentsTest, ToJsonNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const JsonValue expected = create_empty_json_object();

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, ToJsonSetAssetFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const JsonValue expected = AssetFragmentArgumentsTestSuite::create_json_object();
    set_asset_fragment_arguments(class_under_test);

    // Act
    const JsonValue actual = class_under_test.to_json();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    const TestableSharedAssetFragmentArguments lhs;
    const TestableSharedAssetFragmentArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    const TestableSharedAssetFragmentArguments lhs = create_default_arguments();
    const TestableSharedAssetFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedAssetFragmentArguments lhs = create_default_arguments();
    const TestableSharedAssetFragmentArguments rhs;

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    const TestableSharedAssetFragmentArguments lhs;
    const TestableSharedAssetFragmentArguments rhs = create_default_arguments();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
