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
#include "TransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/player/MeltAsset.hpp"
#include "gtest/gtest.h"
#include <string>
#include <vector>

using namespace enjin::sdk::models;
using namespace enjin::sdk::player;
using namespace enjin::test::suites;

class PlayerMeltAssetTest : public TransactionRequestArgumentsTestSuite<MeltAsset>,
                            public JsonTestSuite,
                            public testing::Test {
public:
    MeltAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"melts":[]})";

    static MeltAsset create_default_request() {
        MeltAsset request = MeltAsset()
                .set_melts(std::vector<Melt>());
        set_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(PlayerMeltAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerMeltAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_melts(std::vector<Melt>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerMeltAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    MeltAsset lhs;
    MeltAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerMeltAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    MeltAsset lhs = create_default_request();
    MeltAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerMeltAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    MeltAsset lhs = create_default_request();
    MeltAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PlayerMeltAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    MeltAsset lhs;
    MeltAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
