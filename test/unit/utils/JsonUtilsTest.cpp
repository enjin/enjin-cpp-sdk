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
#include "DummyObject.hpp"
#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"
#include <optional>
#include <string>
#include <vector>

using namespace enjin::sdk::json;
using namespace enjin::sdk::utils;
using namespace enjin::test::utils;

class JsonUtilsTest : public testing::Test {
};

TEST_F(JsonUtilsTest, GetTypeArrayAsJsonValueArrayReturnsJsonArrayWithExpectedData) {
    // Arrange
    const std::string expected_raw = R"([{"id":1}])";
    const std::vector<DummyObject> array = {
            DummyObject::create_default_dummy_object(),
    };

    // Act
    const JsonValue actual = JsonUtils::get_type_array_as_json_value_array(array);

    // Assert
    ASSERT_EQ(expected_raw, actual.to_string());
}

TEST_F(JsonUtilsTest, TryGetArrayAsTypeArrayReturnsTrueAndOutFieldHasExpectedData) {
    // Arrange
    const DummyObject expected = DummyObject::create_default_dummy_object();
    const std::vector input_array = {
            expected,
            expected,
            expected
    };
    const JsonValue value_array = JsonUtils::get_type_array_as_json_value_array(input_array);
    const std::string key = "key";
    JsonValue json_value = JsonValue::create_object();
    std::vector<DummyObject> actual_array;
    const bool is_field_set = json_value.try_set_object_field(key, value_array);

    // Assumptions
    ASSERT_TRUE(is_field_set) << "Assume array was set as object field";

    // Act
    const bool result = JsonUtils::try_get_array_as_type_array(json_value, key, actual_array);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    EXPECT_FALSE(actual_array.empty()) << "Out array is empty";

    for (const DummyObject& actual: actual_array) {
        EXPECT_EQ(expected, actual) << "Actual array element does not equal expected";
    }
}

TEST_F(JsonUtilsTest, TryGetFieldForObjectFieldReturnsTrueAndOutFieldHasExpectedData) {
    // Arrange
    const DummyObject expected = DummyObject::create_default_dummy_object();
    const std::string key = "key";
    JsonValue value_object;
    JsonValue json_value = JsonValue::create_object();
    std::optional<DummyObject> out_field;
    const bool is_value_parsed = value_object.try_parse_as_object(expected.serialize());
    const bool is_field_set = json_value.try_set_object_field(key, value_object);

    // Assumptions
    ASSERT_TRUE(is_value_parsed) << "Assume value object was parsed";
    ASSERT_TRUE(is_field_set) << "Assume object field was set";

    // Act
    const bool result = JsonUtils::try_get_field(json_value, key, out_field);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    ASSERT_TRUE(out_field.has_value()) << "Out field was not set";

    const DummyObject& actual = out_field.value();
    ASSERT_EQ(expected, actual) << "Actual does not equal expected";
}

TEST_F(JsonUtilsTest, TryGetFieldForEmptyFieldReturnsFalseAndOutFieldIsEmpty) {
    // Arrange
    const std::string key = "key";
    JsonValue json_value = JsonValue::create_object();
    std::optional<DummyObject> out_field;

    // Assumptions
    ASSERT_FALSE(json_value.has_object_field(key)) << "Assume object field is not set";

    // Act
    const bool result = JsonUtils::try_get_field(json_value, key, out_field);

    // Assert
    EXPECT_FALSE(result) << "Try-get returned true result";
    ASSERT_FALSE(out_field.has_value()) << "Out field was set";
}

TEST_F(JsonUtilsTest, TryGetFieldGetForArrayFieldReturnsTrueAndOutFieldHasExpectedData) {
    // Arrange
    const DummyObject expected = DummyObject::create_default_dummy_object();
    const std::vector input_array = {
            expected,
            expected,
            expected
    };
    const JsonValue value_array = JsonUtils::get_type_array_as_json_value_array(input_array);
    const std::string key = "key";
    JsonValue json_value = JsonValue::create_object();
    std::optional<std::vector<DummyObject>> out_field;
    const bool is_field_set = json_value.try_set_object_field(key, value_array);

    // Assumptions
    ASSERT_TRUE(is_field_set) << "Assume array was set as object field";

    // Act
    const bool result = JsonUtils::try_get_field(json_value, key, out_field);

    // Assert
    EXPECT_TRUE(result) << "Try-get returned false result";
    ASSERT_TRUE(out_field.has_value()) << "Out field does not have value";

    const std::vector<DummyObject>& actual_array = out_field.value();
    EXPECT_FALSE(actual_array.empty()) << "Actual array is empty";

    for (const DummyObject& actual: actual_array) {
        EXPECT_EQ(expected, actual) << "Actual array element does not equal expected";
    }
}

TEST_F(JsonUtilsTest, TrySetFieldObjectHasFieldAfterAct) {
    // Arrange
    const std::string expected_key = "key";
    const std::optional<DummyObject> in_field(DummyObject::create_default_dummy_object());
    JsonValue json_value = JsonValue::create_object();

    // Assumptions
    ASSERT_TRUE(in_field.has_value()) << "Assume field-optional has a value";
    ASSERT_FALSE(json_value.has_object_field(expected_key)) << "Assume object-value does not have field";

    // Act
    const bool result = JsonUtils::try_set_field(json_value, expected_key, in_field);

    // Assert
    EXPECT_TRUE(result) << "Try-set returned false result";
    ASSERT_TRUE(json_value.has_object_field(expected_key)) << "Object value does not have expected field";
}