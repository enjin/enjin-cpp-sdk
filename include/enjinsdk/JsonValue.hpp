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

#ifndef ENJINSDK_JSONVALUE_HPP
#define ENJINSDK_JSONVALUE_HPP

#include "enjinsdk_export.h"
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace enjin::sdk::json {

/// \brief Public API class for JSON functionality needed by this SDK.
class ENJINSDK_EXPORT JsonValue final {
public:
    /// \brief Creates an instance of this class as a null value type.
    JsonValue();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    JsonValue(const JsonValue& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    JsonValue(JsonValue&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~JsonValue();

    /// \brief Returns a set containing the field keys for this value-object.
    /// \return The set containing the field keys.
    /// \remarks If this value is not a JSON object then the returned set will be empty.
    [[nodiscard]] std::set<std::string> get_object_field_keys() const;

    /// \brief Determines if this value as a JSON object has the specified field.
    /// \param key The field key.
    /// \return Whether this value is a JSON object and has the specified field.
    [[nodiscard]] bool has_object_field(const std::string& key) const;

    /// \brief Determines whether this represents a array value.
    /// \return Whether this represents a array value.
    [[nodiscard]] bool is_array() const;

    /// \brief Determines whether this represents a boolean value.
    /// \return Whether this represents a boolean value.
    [[nodiscard]] bool is_bool() const;

    /// \brief Determines whether this represents a double value.
    /// \return Whether this represents a double value.
    [[nodiscard]] bool is_double() const;

    /// \brief Determines whether this represents a float value.
    /// \return Whether this represents a float value.
    [[nodiscard]] bool is_float() const;

    /// \brief Determines whether this represents a integer value.
    /// \return Whether this represents a integer value.
    [[nodiscard]] bool is_int() const;

    /// \brief Determines whether this represents a 64-bit integer value.
    /// \return Whether this represents a 64-bit integer value.
    [[nodiscard]] bool is_int64() const;

    /// \brief Determines whether this represents a null value.
    /// \return Whether this represents a null value.
    [[nodiscard]] bool is_null() const;

    /// \brief Determines whether this represents a number value.
    /// \return Whether this represents a number value.
    [[nodiscard]] bool is_number() const;

    /// \brief Determines whether this represents a object value.
    /// \return Whether this represents a object value.
    [[nodiscard]] bool is_object() const;

    /// \brief Determines whether this represents a string value.
    /// \return Whether this represents a string value.
    [[nodiscard]] bool is_string() const;

    /// \brief Returns a string representation of this value.
    /// \return The string representation of this value.
    [[nodiscard]] std::string to_string() const;

    /// \brief Tries to clear this value if it is an array.
    /// \return Whether this value was cleared.
    bool try_clear_array();

    /// \brief Tries to clear this value if it is an object.
    /// \return Whether this value was cleared.
    bool try_clear_object();

    /// \brief Tries to get this value as a array and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_array(std::vector<JsonValue>& out) const;

    /// \brief Tries to get this value as a boolean and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_bool(bool& out) const;

    /// \brief Tries to get this value as a double and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_number(double& out) const;

    /// \brief Tries to get this value as a float and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_number(float& out) const;

    /// \brief Tries to get this value as a integer and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_number(int& out) const;

    /// \brief Tries to get this value as a long and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_number(long& out) const;

    /// \brief Tries to get an object field from this value and assign it to an out parameter.
    /// \param key The field key.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_object_field(const std::string& key, JsonValue& out) const;

    /// \brief Tries to get this value as a string and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_string(std::string& out) const;

    /// \brief Tries parsing this value as a JSON object from the given raw JSON.
    /// \param raw The raw JSON.
    /// \return Whether this value was updated.
    bool try_parse_as_object(const std::string& raw);

    /// \brief Tries to remove a object-field for this with the given JSON value.
    /// \param key The field key.
    /// \return Whether the object-field for this was removed.
    bool try_remove_object_field(const std::string& key);

    /// \brief Tries to set an array element for this value with the given element.
    /// \param el The element.
    /// \return Whether the array element was set with the given element.
    bool try_set_array_element(const JsonValue& el);

    /// \brief Tries to set this value with the given boolean.
    /// \param value The value.
    /// \return Whether this value was set with the given boolean.
    bool try_set_bool(bool value);

    /// \brief Tries to set this value with the given double.
    /// \param value The value.
    /// \return Whether this value was set with the given double.
    bool try_set_number(double value);

    /// \brief Tries to set this value with the given float.
    /// \param value The value.
    /// \return Whether this value was set with the given float.
    bool try_set_number(float value);

    /// \brief Tries to set this value with the given integer.
    /// \param value The value.
    /// \return Whether this value was set with the given integer.
    bool try_set_number(int value);

    /// \brief Tries to set this value with the given long.
    /// \param value The value.
    /// \return Whether this value was set with the given integer.
    bool try_set_number(long value);

    /// \brief Tries to set a object-field for this with the given JSON value.
    /// \param key The field key.
    /// \param value The field value.
    /// \return Whether the object-field for this was set with the given value.
    bool try_set_object_field(const std::string& key, const JsonValue& value);

    /// \brief Tries to set this value with the given string.
    /// \param value The value.
    /// \return Whether this value was set with the given string.
    bool try_set_string(const std::string& value);

    bool operator==(const JsonValue& rhs) const;

    bool operator!=(const JsonValue& rhs) const;

    JsonValue& operator=(const JsonValue& rhs);

    /// \brief Creates a array-value instance.
    /// \return The created value instance.
    static JsonValue create_array();

    /// \brief Creates a boolean-value instance.
    /// \return The created value instance.
    static JsonValue create_bool();

    /// \brief Creates a null-value instance.
    /// \return The created value instance.
    static JsonValue create_null();

    /// \brief Creates a number-value instance.
    /// \return The created value instance.
    static JsonValue create_number();

    /// \brief Creates a object-value instance.
    /// \return The created value instance.
    static JsonValue create_object();

    /// \brief Creates a string-value instance.
    /// \return The created value instance.
    static JsonValue create_string();

private:
    /// \brief The implementation class.
    class Impl;

    std::unique_ptr<Impl> pimpl;

    /// \brief Constructs an instance of this class with the given implementation-pointer.
    /// \param ptr The implementation-pointer.
    explicit JsonValue(std::unique_ptr<Impl> ptr);
};

}

#endif //ENJINSDK_JSONVALUE_HPP
