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

#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::graphql;

class AbstractGraphqlRequestTest : public ::testing::Test {
public:
    class TestableGraphqlRequest : public AbstractGraphqlRequest {
    public:
        TestableGraphqlRequest() = delete;

        explicit TestableGraphqlRequest(const std::string& template_key) : AbstractGraphqlRequest(template_key) {
        }

        [[nodiscard]] std::string serialize() const override {
            return std::string();
        }
    };
};

TEST_F(AbstractGraphqlRequestTest, EqualityBothSidesHaveSameTemplateKeyReturnsTrue) {
    // Arrange
    const std::string key("test");
    TestableGraphqlRequest lhs(key);
    TestableGraphqlRequest rhs(key);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AbstractGraphqlRequestTest, EqualityBothSidesHaveDifferentTemplateKeyReturnsFalse) {
    // Arrange
    TestableGraphqlRequest lhs("left");
    TestableGraphqlRequest rhs("right");

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
