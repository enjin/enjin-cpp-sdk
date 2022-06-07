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

#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class OperatorTest : public testing::TestWithParam<std::tuple<std::string, Operator>> {
};

TEST_P(OperatorTest, SerializeOperatorReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    Operator value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_operator(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeOperator,
                         OperatorTest,
                         testing::Values(std::make_tuple("GREATER_THAN", Operator::GreaterThan),
                                         std::make_tuple("GREATER_THAN_OR_EQUAL", Operator::GreaterThanOrEqual),
                                         std::make_tuple("LESS_THAN", Operator::LessThan),
                                         std::make_tuple("LESS_THAN_OR_EQUAL", Operator::LessThanOrEqual)));
