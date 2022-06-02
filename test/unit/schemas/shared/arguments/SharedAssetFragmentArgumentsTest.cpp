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

TEST_F(SharedAssetFragmentArgumentsTest, SerializeNoSetFieldsReturnsEmptyJson) {
    // Arrange
    const std::string expected(EmptyJsonObject);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, SerializeSetAssetFragmentFieldsReturnsExpectedJson) {
    // Arrange
    const std::string expected(AssetFragmentJson);
    set_asset_fragment_arguments(class_under_test);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TestableSharedAssetFragmentArguments lhs;
    TestableSharedAssetFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TestableSharedAssetFragmentArguments lhs = create_default_arguments();
    TestableSharedAssetFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TestableSharedAssetFragmentArguments lhs = create_default_arguments();
    TestableSharedAssetFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedAssetFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TestableSharedAssetFragmentArguments lhs;
    TestableSharedAssetFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
