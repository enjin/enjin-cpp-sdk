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
#include "enjinsdk/ISerializable.hpp"
#include <memory>
#include <string>
#include <vector>

namespace enjin::sdk::json {

/// \brief Public API class for JSON functionality needed by this SDK.
class ENJINSDK_EXPORT JsonValue final : public serialization::ISerializable {
public:
    JsonValue() = delete;

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    JsonValue(const JsonValue& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    JsonValue(JsonValue&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~JsonValue() override;

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

    /// \brief Determines whether this represents a object value.
    /// \return Whether this represents a object value.
    [[nodiscard]] bool is_object() const;

    /// \brief Determines whether this represents a string value.
    /// \return Whether this represents a string value.
    [[nodiscard]] bool is_string() const;

    /// \brief Returns a string representation of this value.
    /// \return The string representation of this value.
    [[nodiscard]] std::string serialize() const override;

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
    bool try_get_double(double& out) const;

    /// \brief Tries to get this value as a float and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_float(float& out) const;

    /// \brief Tries to get this value as a integer and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_int(int& out) const;

    /// \brief Tries to get this value as a 64-bit integer and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_int64(int64_t& out) const;

    /// \brief Tries to get an object field from this value and assign it to an out parameter.
    /// \param key The field key.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_object_field(const std::string& key, JsonValue& out) const;

    /// \brief Tries to get this value as a string and assign it to an out parameter.
    /// \param out The out parameter.
    /// \return Whether the out parameter was set.
    bool try_get_string(std::string& out) const;

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
    bool try_set_double(double value);

    /// \brief Tries to set this value with the given float.
    /// \param value The value.
    /// \return Whether this value was set with the given float.
    bool try_set_float(float value);

    /// \brief Tries to set this value with the given integer.
    /// \param value The value.
    /// \return Whether this value was set with the given integer.
    bool try_set_int(int value);

    /// \brief Tries to set this value with the given 64-bit integer.
    /// \param value The value.
    /// \return Whether this value was set with the given 64-bit integer.
    bool try_set_int64(int64_t value);

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
