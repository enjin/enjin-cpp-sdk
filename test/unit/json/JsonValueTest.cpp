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
#include <vector>

using namespace enjin::sdk::json;

class JsonValueTest : public testing::Test {
public:
    static JsonValue create_int_value() {
        JsonValue value = JsonValue::create_number();
        value.try_set_int(1);
        return value;
    }
};

TEST_F(JsonValueTest, TryGetArrayWithSetValueReturnsTrueAndOutParamHasExpectedElements) {
    // Arrange
    const JsonValue expected_element = create_int_value();
    std::vector<JsonValue> actual;
    JsonValue json_value = JsonValue::create_array();
    const bool is_element_set = json_value.try_set_array_element(expected_element);

    // Assumptions
    ASSERT_TRUE(is_element_set) << "Assume array-element was set";

    // Act
    const bool result = json_value.try_get_array(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-getter returned false result";
    ASSERT_FALSE(actual.empty()) << "Out array is empty";

    for (const JsonValue& actual_element: actual) {
        EXPECT_EQ(expected_element, actual_element) << "Element in out array does not equal expected";
    }
}

TEST_F(JsonValueTest, TryGetBoolWithSetValueReturnsTrueAndOutParamEqualsExpected) {
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
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetDoubleWithSetValueReturnsTrueAndOutParamEqualsExpected) {
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
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetFloatWithSetValueReturnsTrueAndOutParamEqualsExpected) {
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
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetIntWithSetValueReturnsTrueAndOutParamEqualsExpected) {
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
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetInt64WithSetValueReturnsTrueAndOutParamEqualsExpected) {
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
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetObjectWithSetValueReturnsTrueAndOutParamEqualsExpected) {
    // Arrange
    const std::string expected_key = "key";
    const JsonValue expected_value = create_int_value();
    JsonValue actual;
    JsonValue json_value = JsonValue::create_object();
    const bool is_field_set = json_value.try_set_object_field(expected_key, expected_value);

    // Assumptions
    ASSERT_TRUE(is_field_set) << "Assume object-field was set";

    // Act
    const bool result = json_value.try_get_object_field(expected_key, actual);

    // Assert
    EXPECT_TRUE(result) << "Try-getter returned false result";
    EXPECT_EQ(expected_value, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetStringWithSetValueReturnsTrueAndOutParamEqualsExpected) {
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
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TrySetArrayElementOnArrayValueReturnsTrue) {
    // Arrange
    const JsonValue element = create_int_value();
    JsonValue json_value = JsonValue::create_array();

    // Act
    const bool actual = json_value.try_set_array_element(element);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetArrayElementOnNonArrayValueReturnsFalse) {
    // Arrange
    const JsonValue element = create_int_value();
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_array_element(element);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetBoolOnBoolValueReturnsTrue) {
    // Arrange
    const bool value = true;
    JsonValue json_value = JsonValue::create_bool();

    // Act
    const bool actual = json_value.try_set_bool(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetBoolOnNonBoolValueReturnsFalse) {
    // Arrange
    const bool value = true;
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_bool(value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetDoubleOnNumberValueReturnsTrue) {
    // Arrange
    const double value = 1.0;
    JsonValue json_value = JsonValue::create_number();

    // Act
    const bool actual = json_value.try_set_double(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetDoubleOnNonNumberValueReturnsFalse) {
    // Arrange
    const double value = 1.0;
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_double(value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetFloatOnNumberValueReturnsTrue) {
    // Arrange
    const float value = 1.0;
    JsonValue json_value = JsonValue::create_number();

    // Act
    const bool actual = json_value.try_set_float(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetFloatOnNonNumberValueReturnsFalse) {
    // Arrange
    const float value = 1.0;
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_float(value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetIntOnNumberValueReturnsTrue) {
    // Arrange
    const int value = 1;
    JsonValue json_value = JsonValue::create_number();

    // Act
    const bool actual = json_value.try_set_int(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetIntOnNonNumberValueReturnsFalse) {
    // Arrange
    const int value = 1;
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_int(value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetInt64OnNumberValueReturnsTrue) {
    // Arrange
    const int64_t value = 1;
    JsonValue json_value = JsonValue::create_number();

    // Act
    const bool actual = json_value.try_set_int64(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetInt64OnNonNumberValueReturnsFalse) {
    // Arrange
    const int64_t value = 1;
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_int64(value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetObjectFieldOnObjectValueReturnsTrue) {
    // Arrange
    const std::string key = "key";
    const JsonValue value = create_int_value();
    JsonValue json_value = JsonValue::create_object();

    // Act
    const bool actual = json_value.try_set_object_field(key, value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetObjectFieldOnNonObjectValueReturnsFalse) {
    // Arrange
    const std::string key = "key";
    const JsonValue value = create_int_value();
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_object_field(key, value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetStringOnStringValueReturnsTrue) {
    // Arrange
    const std::string value = "xyz";
    JsonValue json_value = JsonValue::create_string();

    // Act
    const bool actual = json_value.try_set_string(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetStringOnNonStringValueReturnsFalse) {
    // Arrange
    const std::string value = "xyz";
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_string(value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, EqualityValuesAreArraysBothSidesAreEmptyReturnsTrue) {
    // Arrange
    const JsonValue lhs = JsonValue::create_array();
    const JsonValue rhs = JsonValue::create_array();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, EqualityValuesAreArraysLeftSideIsEmptyReturnsFalse) {
    // Arrange
    const JsonValue lhs = JsonValue::create_array();
    JsonValue rhs = JsonValue::create_array();
    JsonValue fake_value = create_int_value();
    rhs.try_set_array_element(fake_value);

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, EqualityValuesAreArraysRightSideIsEmptyReturnsFalse) {
    // Arrange
    JsonValue lhs = JsonValue::create_array();
    const JsonValue rhs = JsonValue::create_array();
    JsonValue fake_value = create_int_value();
    lhs.try_set_array_element(fake_value);

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, EqualityValuesAreArraysBothSidesHaveSameElementReturnsTrue) {
    // Arrange
    JsonValue lhs = JsonValue::create_array();
    JsonValue rhs = JsonValue::create_array();
    JsonValue fake_value = create_int_value();
    lhs.try_set_array_element(fake_value);
    rhs.try_set_array_element(fake_value);

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, EqualityValuesAreObjectsBothSidesAreEmptyReturnsTrue) {
    // Arrange
    const JsonValue lhs = JsonValue::create_object();
    const JsonValue rhs = JsonValue::create_object();

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, EqualityValuesAreObjectsLeftSideIsEmptyReturnsFalse) {
    // Arrange
    JsonValue lhs = JsonValue::create_object();
    JsonValue rhs = JsonValue::create_object();
    const std::string key = "key";
    JsonValue value = create_int_value();
    rhs.try_set_object_field(key, value);

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, EqualityValuesAreObjectsRightSideIsEmptyReturnsFalse) {
    // Arrange
    JsonValue lhs = JsonValue::create_object();
    JsonValue rhs = JsonValue::create_object();
    const std::string key = "key";
    JsonValue value = create_int_value();
    lhs.try_set_object_field(key, value);

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, EqualityValuesAreObjectsBothSidesHaveSameFieldsReturnsTrue) {
    // Arrange
    JsonValue lhs = JsonValue::create_object();
    JsonValue rhs = JsonValue::create_object();
    const std::string key = "key";
    JsonValue value = create_int_value();
    lhs.try_set_object_field(key, value);
    rhs.try_set_object_field(key, value);

    // Act
    const bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}
