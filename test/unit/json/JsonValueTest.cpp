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
#include "enjinsdk/JsonValue.hpp"
#include <string>

using namespace enjin::sdk::json;

class JsonValueTest : public testing::Test {
};

TEST_F(JsonValueTest, SomeTest) {
    // Arrange

    // Act

    // Assert
    FAIL() << "Test not implemented";
}

TEST_F(JsonValueTest, TryGetArrayWithSetValueReturnsExpected) {
    // Arrange

    // Act

    // Assert
    FAIL() << "Test not implemented";
}

TEST_F(JsonValueTest, TryGetBoolWithSetValueReturnsExpected) {
    // Arrange
    const bool expected = true;
    bool actual;
    JsonValue json_value = JsonValue::create_bool();
    const bool is_value_set = json_value.try_set_bool(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume bool-value was set";

    // Act
    const bool result = json_value.try_get_bool(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-getter returned false result";
    EXPECT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, TryGetDoubleWithSetValueReturnsExpected) {
    // Arrange
    const double expected = 1.0;
    double actual;
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_double(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume double-value was set";

    // Act
    const bool result = json_value.try_get_double(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-getter returned false result";
    EXPECT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, TryGetFloatWithSetValueReturnsExpected) {
    // Arrange
    const float expected = 1.0;
    float actual;
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_float(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume float-value was set";

    // Act
    const bool result = json_value.try_get_float(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-getter returned false result";
    EXPECT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, TryGetIntWithSetValueReturnsExpected) {
    // Arrange
    const int expected = 1;
    int actual;
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_int(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume int-value was set";

    // Act
    const bool result = json_value.try_get_int(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-getter returned false result";
    EXPECT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, TryGetInt64WithSetValueReturnsExpected) {
    // Arrange
    const int64_t expected = 1;
    int64_t actual;
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_int64(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume int64-value was set";

    // Act
    const bool result = json_value.try_get_int64(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-getter returned false result";
    EXPECT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, TryGetObjectWithSetValueReturnsExpected) {
    // Arrange

    // Act

    // Assert
    FAIL() << "Test not implemented";
}

TEST_F(JsonValueTest, TryGetStringWithSetValueReturnsExpected) {
    // Arrange
    const std::string expected = "xyz";
    std::string actual;
    JsonValue json_value = JsonValue::create_string();
    const bool is_value_set = json_value.try_set_string(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume string-value was set";

    // Act
    const bool result = json_value.try_get_string(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-getter returned false result";
    EXPECT_EQ(expected, actual) << "Actual does not equal expected";
}
