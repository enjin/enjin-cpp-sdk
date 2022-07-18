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
#include <set>
#include <string>
#include <vector>

using namespace enjin::sdk::json;

class JsonValueTest : public testing::Test {
public:
    static JsonValue create_int_value() {
        JsonValue value = JsonValue::create_number();
        value.try_set_number(1);
        return value;
    }

    static JsonValue create_object_value() {
        JsonValue value = JsonValue::create_object();

        JsonValue sub_value = JsonValue::create_string();
        sub_value.try_set_string("value");
        value.try_set_object_field("key", sub_value);

        return value;
    }
};

TEST_F(JsonValueTest, GetObjectFieldKeysWithSetFieldReturnsExpectedKeys) {
    // Arrange
    const std::string expected_key = "key";
    JsonValue json_value = JsonValue::create_object();
    const JsonValue dummy_value = create_int_value();
    const bool is_field_set = json_value.try_set_object_field(expected_key, dummy_value);

    // Assumptions
    ASSERT_TRUE(is_field_set) << "Assume object-field was set";

    // Act
    const std::set<std::string> actual = json_value.get_object_field_keys();

    // Assert
    EXPECT_FALSE(actual.empty()) << "Key-set is empty";
    EXPECT_FALSE(actual.find(expected_key) == actual.end()) << "Key-set does not contain expected key";
}

TEST_F(JsonValueTest, HasObjectFieldFieldIsSetOnObjectValueReturnsTrue) {
    // Arrange
    const std::string key = "key";
    JsonValue json_value = JsonValue::create_object();
    const JsonValue dummy_value = create_int_value();
    const bool is_field_set = json_value.try_set_object_field(key, dummy_value);

    // Assumptions
    ASSERT_TRUE(is_field_set) << "Assume object-field was set";

    // Act
    const bool actual = json_value.has_object_field(key);

    // Assert
    ASSERT_TRUE(actual) << "Has object field returned false";
}

TEST_F(JsonValueTest, HasObjectFieldFieldIsNotSetOnObjectValueReturnsFalse) {
    // Arrange
    const std::string key = "key";
    JsonValue json_value = JsonValue::create_object();

    // Act
    const bool actual = json_value.has_object_field(key);

    // Assert
    ASSERT_FALSE(actual) << "Has object field returned true";
}

TEST_F(JsonValueTest, ToStringOnArrayValueReturnsExpected) {
    // Arrange
    const std::string expected = R"([1])";
    JsonValue json_value = JsonValue::create_array();
    JsonValue dummy_element = create_int_value();
    const bool is_element_set = json_value.try_set_array_element(dummy_element);

    // Assumptions
    ASSERT_TRUE(is_element_set) << "Assume element was set in array";

    // Act
    const std::string actual = json_value.to_string();

    // Assert
    ASSERT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, ToStringOnBoolValueReturnsExpected) {
    // Arrange
    const std::string expected = R"(true)";
    JsonValue json_value = JsonValue::create_bool();
    const bool is_value_set = json_value.try_set_bool(true);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume value was set";

    // Act
    const std::string actual = json_value.to_string();

    // Assert
    ASSERT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, ToStringOnDoubleValueReturnsExpected) {
    // Arrange
    const std::string expected = R"(1.0)";
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_number(1.0);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume value was set";

    // Act
    const std::string actual = json_value.to_string();

    // Assert
    ASSERT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, ToStringOnFloatValueReturnsExpected) {
    // Arrange
    const std::string expected = R"(1.0)";
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_number(1.0f);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume value was set";

    // Act
    const std::string actual = json_value.to_string();

    // Assert
    ASSERT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, ToStringOnIntValueReturnsExpected) {
    // Arrange
    const std::string expected = R"(1)";
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_number(1);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume value was set";

    // Act
    const std::string actual = json_value.to_string();

    // Assert
    ASSERT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, ToStringOnInt64ValueReturnsExpected) {
    // Arrange
    const std::string expected = R"(1)";
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_number(1L);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume value was set";

    // Act
    const std::string actual = json_value.to_string();

    // Assert
    ASSERT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, ToStringOnObjectValueReturnsExpected) {
    // Arrange
    const std::string expected = R"({"key":"value"})";
    JsonValue json_value = JsonValue::create_object();
    JsonValue fake_field = JsonValue::create_string();
    const bool is_field_value_set = fake_field.try_set_string("value");
    const bool is_field_set = json_value.try_set_object_field("key", fake_field);

    // Assumptions
    ASSERT_TRUE(is_field_value_set) << "Assume value was set in field";
    ASSERT_TRUE(is_field_set) << "Assume field was set in object";

    // Act
    const std::string actual = json_value.to_string();

    // Assert
    ASSERT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, ToStringOnStringValueReturnsExpected) {
    // Arrange
    const std::string expected = R"("xyz")";
    JsonValue json_value = JsonValue::create_string();
    const bool is_value_set = json_value.try_set_string("xyz");

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume value was set";

    // Act
    const std::string actual = json_value.to_string();

    // Assert
    ASSERT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonValueTest, TryClearArrayOnArrayValueReturnsTrue) {
    // Arrange
    JsonValue json_value = JsonValue::create_array();

    // Act
    const bool result = json_value.try_clear_array();

    // Assert
    ASSERT_TRUE(result);
}

TEST_F(JsonValueTest, TryClearArrayOnNonArrayValueReturnsFalse) {
    // Arrange
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool result = json_value.try_clear_array();

    // Assert
    ASSERT_FALSE(result);
}

TEST_F(JsonValueTest, TryClearObjectOnObjectValueReturnsTrue) {
    // Arrange
    JsonValue json_value = JsonValue::create_object();

    // Act
    const bool result = json_value.try_clear_object();

    // Assert
    ASSERT_TRUE(result);
}

TEST_F(JsonValueTest, TryClearObjectOnNonObjectValueReturnsFalse) {
    // Arrange
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool result = json_value.try_clear_object();

    // Assert
    ASSERT_FALSE(result);
}

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
    EXPECT_TRUE(result) << "Try-get returned false result";
    ASSERT_FALSE(actual.empty()) << "Out array is empty";

    for (const JsonValue& actual_element: actual) {
        EXPECT_EQ(expected_element, actual_element) << "Element in out array does not equal expected";
    }
}

TEST_F(JsonValueTest, TryGetArrayWithSetValueBeforeTryClearArrayReturnsTrueAndOutParamIsEmpty) {
    // Arrange
    std::vector<JsonValue> actual;
    JsonValue json_value = JsonValue::create_array();
    const JsonValue dummy_element = create_int_value();
    actual.push_back(dummy_element);
    const bool is_element_set = json_value.try_set_array_element(dummy_element);
    const bool is_array_clear = json_value.try_clear_array();

    // Assumptions
    ASSERT_FALSE(actual.empty()) << "Assume out array is not empty before act";
    ASSERT_TRUE(is_element_set) << "Assume array-element was set";
    ASSERT_TRUE(is_array_clear) << "Assume array was cleared";

    // Act
    const bool result = json_value.try_get_array(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_TRUE(actual.empty()) << "Out array is not empty";
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
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetNumberWithSetDoubleValueReturnsTrueAndOutParamEqualsExpected) {
    // Arrange
    const double expected = 1.0;
    double actual;
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_number(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume double-value was set";

    // Act
    const bool result = json_value.try_get_number(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetNumberWithSetFloatValueReturnsTrueAndOutParamEqualsExpected) {
    // Arrange
    const float expected = 1.0;
    float actual;
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_number(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume float-value was set";

    // Act
    const bool result = json_value.try_get_number(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetNumberWithSetIntValueReturnsTrueAndOutParamEqualsExpected) {
    // Arrange
    const int expected = 1;
    int actual;
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_number(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume int-value was set";

    // Act
    const bool result = json_value.try_get_number(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetNumberWithSetLongValueReturnsTrueAndOutParamEqualsExpected) {
    // Arrange
    const long expected = 1L;
    long actual;
    JsonValue json_value = JsonValue::create_number();
    const bool is_value_set = json_value.try_set_number(expected);

    // Assumptions
    ASSERT_TRUE(is_value_set) << "Assume int64-value was set";

    // Act
    const bool result = json_value.try_get_number(actual);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetObjectFieldWithNoSetValueReturnsTrueAndOutParamIsNullValue) {
    // Arrange
    JsonValue actual = create_int_value();
    JsonValue json_value = JsonValue::create_object();
    const std::string dummy_key = "key";

    // Assumptions
    ASSERT_FALSE(actual.is_null()) << "Assume out param is not null value before act";

    // Act
    const bool result = json_value.try_get_object_field(dummy_key, actual);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_TRUE(actual.is_null()) << "Out param is not null value";
}

TEST_F(JsonValueTest, TryGetObjectFieldWithSetValueReturnsTrueAndOutParamEqualsExpected) {
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
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_EQ(expected_value, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryGetObjectFieldWithSetValueBeforeTryClearObjectReturnsTrueAndOutParamIsNullValue) {
    // Arrange
    JsonValue actual = create_int_value();
    JsonValue json_value = JsonValue::create_object();
    const std::string dummy_key = "key";
    const JsonValue dummy_value = create_int_value();
    const bool is_field_set = json_value.try_set_object_field(dummy_key, dummy_value);
    const bool is_object_clear = json_value.try_clear_object();

    // Assumptions
    ASSERT_TRUE(is_field_set) << "Assume object-field was set";
    ASSERT_TRUE(is_object_clear) << "Assume object was cleared";
    ASSERT_FALSE(actual.is_null()) << "Assume out param is not null value before act";

    // Act
    const bool result = json_value.try_get_object_field(dummy_key, actual);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_TRUE(actual.is_null()) << "Out param is not null value";
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
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_EQ(expected, actual) << "Out param does not equal expected";
}

TEST_F(JsonValueTest, TryParseAsObjectWithValidJsonReturnsTrue) {
    // Arrange
    const JsonValue expected = create_object_value();
    const std::string raw = expected.to_string();
    JsonValue actual;

    // Assumptions
    ASSERT_FALSE(actual.is_object()) << "Assume value is not an object before parse";

    // Act
    const bool result = actual.try_parse_as_object(raw);

    // Assert
    EXPECT_TRUE(result) << "Try-parse returned false result";
    EXPECT_TRUE(actual.is_object()) << "Value was not set as an object after parse";
    EXPECT_EQ(expected, actual) << "Value does not equal expected";
}

TEST_F(JsonValueTest, TryParseAsObjectWithNonObjectJsonReturnsFalse) {
    // Arrange
    const std::string raw = R"(1)";
    JsonValue json_value;

    // Assumptions
    ASSERT_FALSE(json_value.is_object()) << "Assume value is not an object before parse";

    // Act
    const bool actual = json_value.try_parse_as_object(raw);

    // Assert
    EXPECT_FALSE(actual) << "Try-parse returned true result";
    EXPECT_FALSE(json_value.is_object()) << "Value was set as an object after parse";
}

TEST_F(JsonValueTest, TryParseAsObjectWithMalformedJsonReturnsFalse) {
    // Arrange
    const std::string raw = R"({{})";
    JsonValue json_value;

    // Assumptions
    ASSERT_FALSE(json_value.is_object()) << "Assume value is not an object before parse";

    // Act
    const bool actual = json_value.try_parse_as_object(raw);

    // Assert
    EXPECT_FALSE(actual) << "Try-parse returned true result";
    EXPECT_FALSE(json_value.is_object()) << "Value was set as an object after parse";
}

TEST_F(JsonValueTest, TryRemoveObjectFieldWithSetValueReturnsTrue) {
    // Arrange
    const std::string key = "key";
    const JsonValue dummy_value = create_int_value();
    JsonValue json_value = JsonValue::create_object();
    const bool is_field_set = json_value.try_set_object_field(key, dummy_value);

    // Assumptions
    ASSERT_TRUE(is_field_set) << "Assume object-field was set";

    // Act
    const bool actual = json_value.try_remove_object_field(key);

    // Assert
    ASSERT_TRUE(actual) << "Try-remove returned false result";
}

TEST_F(JsonValueTest, TryRemoveObjectFieldWithNoSetValueReturnsFalse) {
    // Arrange
    const std::string key = "key";
    JsonValue json_value = JsonValue::create_object();

    // Act
    const bool actual = json_value.try_remove_object_field(key);

    // Assert
    ASSERT_FALSE(actual);
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

TEST_F(JsonValueTest, TrySetNumberGivenDoubleOnNumberValueReturnsTrue) {
    // Arrange
    const double value = 1.0;
    JsonValue json_value = JsonValue::create_number();

    // Act
    const bool actual = json_value.try_set_number(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetNumberGivenDoubleOnNonNumberValueReturnsFalse) {
    // Arrange
    const double value = 1.0;
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_number(value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetNumberGivenFloatOnNumberValueReturnsTrue) {
    // Arrange
    const float value = 1.0;
    JsonValue json_value = JsonValue::create_number();

    // Act
    const bool actual = json_value.try_set_number(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetNumberGivenFloatOnNonNumberValueReturnsFalse) {
    // Arrange
    const float value = 1.0;
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_number(value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetNumberGivenIntOnNumberValueReturnsTrue) {
    // Arrange
    const int value = 1;
    JsonValue json_value = JsonValue::create_number();

    // Act
    const bool actual = json_value.try_set_number(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetNumberGivenIntOnNonNumberValueReturnsFalse) {
    // Arrange
    const int value = 1;
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_number(value);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(JsonValueTest, TrySetNumberGivenLongOnNumberValueReturnsTrue) {
    // Arrange
    const long value = 1L;
    JsonValue json_value = JsonValue::create_number();

    // Act
    const bool actual = json_value.try_set_number(value);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(JsonValueTest, TrySetNumberGivenLongOnNonNumberValueReturnsFalse) {
    // Arrange
    const long value = 1L;
    JsonValue json_value = JsonValue::create_null();

    // Act
    const bool actual = json_value.try_set_number(value);

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

TEST_F(JsonValueTest, TrySetObjectFieldObjectAlreadyHasFieldOverridesOldField) {
    // Arrange
    const std::string expected_key = "key";
    const JsonValue expected_value = create_object_value();
    JsonValue actual_value;
    JsonValue json_value = JsonValue::create_object();
    const JsonValue dummy_value = create_int_value();
    const bool is_field_set = json_value.try_set_object_field(expected_key, dummy_value);

    // Assumptions
    ASSERT_TRUE(is_field_set) << "Assume field to be overridden was set";
    ASSERT_TRUE(json_value.has_object_field(expected_key)) << "Assume value-object has field";

    // Act
    const bool result = json_value.try_set_object_field(expected_key, expected_value);

    // Assert
    EXPECT_TRUE(result) << "Try-setter returned false result";
    EXPECT_TRUE(json_value.has_object_field(expected_key)) << "Value-object no longer has field for expected key";

    json_value.try_get_object_field(expected_key, actual_value);
    EXPECT_EQ(expected_value, actual_value) << "Actual field-value does not equal expected";
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
