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

#ifndef ENJINSDK_JSONUTILS_HPP
#define ENJINSDK_JSONUTILS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/EnumUtils.hpp"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/JsonValue.hpp"
#include "enjinsdk/models/AssetField.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include "enjinsdk/models/AssetIndexFormat.hpp"
#include "enjinsdk/models/AssetSupplyModel.hpp"
#include "enjinsdk/models/AssetTransferFeeType.hpp"
#include "enjinsdk/models/AssetTransferable.hpp"
#include "enjinsdk/models/AssetVariantMode.hpp"
#include "enjinsdk/models/Operator.hpp"
#include "enjinsdk/models/TransactionState.hpp"
#include "enjinsdk/models/TransactionType.hpp"
#include "enjinsdk/models/SortDirection.hpp"
#include "enjinsdk/models/TransactionField.hpp"
#include "enjinsdk/models/Whitelisted.hpp"
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace enjin::sdk::utils {

/// \brief Utility class for JSON processing.
class ENJINSDK_EXPORT JsonUtils final {
public:
    JsonUtils() = delete;

    ~JsonUtils() = delete;

    /// \brief Creates a JSON value-array from a typed array.
    /// \tparam T The type contained within the array being processed.
    /// \param array The array being processed.
    /// \return The JSON value-array.
    /// \remarks Class type T must implement Serialization::ISerializable.
    template<class T>
    static json::JsonValue get_type_array_as_json_value_array(const std::vector<T>& array) {
        static_assert(std::is_base_of_v<serialization::ISerializable, T>,
                      "Class T does not inherit from ISerializable.");

        json::JsonValue value_array = json::JsonValue::create_array();

        for (const T& el: array) {
            value_array.try_set_array_element(el.to_json());
        }

        return value_array;
    }

    /// \brief Joins one JSON object to another.
    /// \param json The JSON object being modified.
    /// \param other The JSON object to copy fields from.
    static void join_object(json::JsonValue& json, const json::JsonValue& other);

    /// \brief Tries to get the specified object field as a typed array.
    /// \tparam T The class type the array stores.
    /// \param json The JSON value-object.
    /// \param key The name of the field.
    /// \param out The array being set.
    /// \return Whether this action was successful.
    /// \remarks Class type T must implement Serialization::IDeserializable.
    template<class T>
    static bool try_get_array_as_type_array(const json::JsonValue& json, const std::string& key, std::vector<T>& out) {
        static_assert(std::is_base_of_v<serialization::IDeserializable, T>,
                      "Class T does not inherit from IDeserializable.");

        if (!json.is_object()) {
            return false;
        }

        json::JsonValue array;
        if (!json.try_get_object_field(key, array)) {
            return false;
        }

        std::vector<json::JsonValue> value_array;
        if (!array.try_get_array(value_array)) {
            return false;
        }

        out.clear();

        for (const json::JsonValue& value: value_array) {
            T t;
            t.deserialize(value.to_string());

            out.push_back(std::move(t));
        }

        return true;
    }

    /// \brief Tries and set the optional with the specified field.
    /// \tparam T The class type of the object.
    /// \param json The JSON value-object.
    /// \param key The name of the field.
    /// \param out_field The optional to write to.
    /// \return Whether this action was successful.
    /// \remarks The out optional will be cleared if this operation is not successful.
    template<class T>
    static bool try_get_field(const json::JsonValue& json, const std::string& key, std::optional<T>& out_field) {
        T new_field;

        if (try_get_object_as_type<T>(json, key, new_field)) {
            out_field.emplace(std::move(new_field));
            return true;
        }

        out_field.reset();
        return false;
    }

    /// \brief Tries and set the optional with the specified array field.
    /// \tparam T The class type contained in the array.
    /// \param json The JSON value-object.
    /// \param key The name of the field.
    /// \param out_field The optional to write to.
    /// \return Whether this action was successful.
    /// \remarks The out optional will be cleared if this operation is not successful.
    template<class T>
    static bool try_get_field(const json::JsonValue& json,
                              const std::string& key,
                              std::optional<std::vector<T>>& out_field) {
        std::vector<T> new_field;

        if (try_get_array_as_type_array<T>(json, key, new_field)) {
            out_field.emplace(std::move(new_field));
            return true;
        }

        out_field.reset();
        return false;
    }

    /// \brief Tries to get the specified object field as an instance of the class type.
    /// \tparam T The class type of the object.
    /// \param json The JSON value-object.
    /// \param key The name of the field.
    /// \param out The object being set.
    /// \return Whether this action was successful.
    /// \remarks Class type T must implement Serialization::IDeserializable.
    template<class T>
    static bool try_get_object_as_type(const json::JsonValue& json, const std::string& key, T& out) {
        static_assert(std::is_base_of_v<serialization::IDeserializable, T>,
                      "Class T does not inherit from IDeserializable.");

        json::JsonValue value = json::JsonValue::create_object();
        if (!json.try_get_object_field(key, value) || !value.is_object()) {
            return false;
        }

        out.deserialize(value.to_string());
        return true;
    }

    /// \brief Tries and set the specified field in the JSON value-object with the data contained within the optional.
    /// \tparam T The class type of the object.
    /// \param json The JSON value-object.
    /// \param key The name of the field.
    /// \param in_field The optional containing the data to set.
    /// \return Whether this action was successful.
    /// \remarks If the value-object already has the field and the optional is empty, then the field will be removed.
    template<class T>
    static bool try_set_field(json::JsonValue& json, const std::string& key, const std::optional<T>& in_field) {
        static_assert(std::is_base_of_v<serialization::ISerializable, T>,
                      "Class T does not inherit from ISerializable.");

        if (in_field.has_value()) {
            json.try_set_object_field(key, in_field.value().to_json());
            return true;
        }

        json.try_remove_object_field(key);
        return false;
    }

    /// \brief Tries and set the specified field in the JSON value-object with the array contained within the optional.
    /// \tparam T The class type of the object.
    /// \param json The JSON value-object.
    /// \param key The name of the field.
    /// \param in_field The array containing the data to set.
    /// \return Whether this action was successful.
    /// \remarks If the value-object already has the field and the optional is empty, then the field will be removed.
    template<class T>
    static bool try_set_field(json::JsonValue& json,
                              const std::string& key,
                              const std::optional<std::vector<T>>& in_field) {
        static_assert(std::is_base_of_v<serialization::ISerializable, T>,
                      "Class T does not inherit from ISerializable.");

        if (in_field.has_value()) {
            json.try_set_object_field(key, get_type_array_as_json_value_array(in_field.value()));
            return true;
        }

        json.try_remove_object_field(key);
        return false;
    }
};

/// \brief Creates a JSON value-array from a string array.
/// \param array The array being processed.
/// \return The JSON value-array.
template<>
inline json::JsonValue JsonUtils::get_type_array_as_json_value_array(const std::vector<std::string>& array) {
    json::JsonValue value_array = json::JsonValue::create_array();

    for (const std::string& el: array) {
        json::JsonValue value_string = json::JsonValue::create_string();

        if (value_string.try_set_string(el)) {
            value_array.try_set_array_element(value_string);
        }
    }

    return value_array;
}

/// \brief Tries and set the optional with the specified bool field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<bool>& out_field) {
    bool new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_bool(new_field)) {
        out_field = new_field;
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified double field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<double>& out_field) {
    double new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_number(new_field)) {
        out_field = new_field;
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified float field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<float>& out_field) {
    float new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_number(new_field)) {
        out_field = new_field;
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified integer field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<int>& out_field) {
    int new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_number(new_field)) {
        out_field = new_field;
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified long field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<long>& out_field) {
    long new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_number(new_field)) {
        out_field = new_field;
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified JSON value field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<json::JsonValue>& out_field) {
    json::JsonValue new_field;

    if (json.try_get_object_field(key, new_field) && new_field.is_object()) {
        out_field.emplace(std::move(new_field));
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified array of JSON values field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<std::vector<json::JsonValue>>& out_field) {
    std::vector<json::JsonValue> value_array;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_array(value_array)) {
        out_field.emplace(std::move(value_array));
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified string field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<std::string>& out_field) {
    std::string new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_string(new_field)) {
        out_field.emplace(std::move(new_field));
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified string-array field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<std::vector<std::string>>& out_field) {
    std::vector<json::JsonValue> value_array;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_array(value_array)) {
        std::vector<std::string> new_field;

        for (const json::JsonValue& el: value_array) {
            new_field.push_back(el.to_string());
        }

        out_field.emplace(std::move(new_field));
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified enum field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<models::AssetSupplyModel>& out_field) {
    std::string new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_string(new_field)) {
        out_field = EnumUtils::deserialize_asset_supply_model(new_field);
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified enum field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<models::AssetTransferFeeType>& out_field) {
    std::string new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_string(new_field)) {
        out_field = EnumUtils::deserialize_asset_transfer_fee_type(new_field);
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified enum field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<models::AssetTransferable>& out_field) {
    std::string new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_string(new_field)) {
        out_field = EnumUtils::deserialize_asset_transferable(new_field);
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified enum field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<models::AssetVariantMode>& out_field) {
    std::string new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_string(new_field)) {
        out_field = EnumUtils::deserialize_asset_variant_mode(new_field);
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified enum field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<models::TransactionState>& out_field) {
    std::string new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_string(new_field)) {
        out_field = EnumUtils::deserialize_transaction_state(new_field);
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the optional with the specified enum field.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param out_field The optional to write to.
/// \return Whether this action was successful.
/// \remarks The out optional will be cleared if this operation is not successful.
template<>
inline bool JsonUtils::try_get_field(const json::JsonValue& json,
                                     const std::string& key,
                                     std::optional<models::TransactionType>& out_field) {
    std::string new_field;
    json::JsonValue value;

    if (json.try_get_object_field(key, value) && value.try_get_string(new_field)) {
        out_field = EnumUtils::deserialize_transaction_type(new_field);
        return true;
    }

    out_field.reset();
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the boolean contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<bool>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_bool();
        value.try_set_bool(in_field.value());

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the double contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<double>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_number();
        value.try_set_number(in_field.value());

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the float contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<float>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_number();
        value.try_set_number(in_field.value());

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the integer contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<int>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_number();
        value.try_set_number(in_field.value());

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the long contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<long>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_number();
        value.try_set_number(in_field.value());

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the JSON value contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<json::JsonValue>& in_field) {
    if (in_field.has_value()) {
        json.try_set_object_field(key, in_field.value());
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the string contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<std::string>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(in_field.value());

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the string array contained within the
/// optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<std::vector<std::string>>& in_field) {
    if (in_field.has_value()) {
        json.try_set_object_field(key, JsonUtils::get_type_array_as_json_value_array(in_field.value()));
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::AssetField>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_asset_field(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::AssetIdFormat>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_asset_id_format(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::AssetIndexFormat>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_asset_index_format(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::AssetSupplyModel>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_asset_supply_model(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::AssetTransferFeeType>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_asset_transfer_fee_type(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::AssetTransferable>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_asset_transferable(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::Operator>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_operator(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::SortDirection>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_sort_direction(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::TransactionField>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_transaction_field(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::TransactionState>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_transaction_state(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum array contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<std::vector<models::TransactionState>>& in_field) {
    if (in_field.has_value()) {
        std::vector<std::string> states;

        for (const models::TransactionState type: in_field.value()) {
            states.push_back(EnumUtils::serialize_transaction_state(type));
        }

        const std::optional<std::vector<std::string>> opt(std::move(states));
        return JsonUtils::try_set_field(json, key, opt);
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::TransactionType>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_transaction_type(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum array contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<std::vector<models::TransactionType>>& in_field) {
    if (in_field.has_value()) {
        std::vector<std::string> types;

        for (const models::TransactionType type: in_field.value()) {
            types.push_back(EnumUtils::serialize_transaction_type(type));
        }

        const std::optional<std::vector<std::string>> opt(std::move(types));
        return JsonUtils::try_set_field(json, key, opt);
    }

    json.try_remove_object_field(key);
    return false;
}

/// \brief Tries and set the specified field in the JSON value-object with the enum contained within the optional.
/// \param json The JSON value-object.
/// \param key The name of the field.
/// \param in_field The boolean to set.
/// \return Whether this action was successful.
template<>
inline bool JsonUtils::try_set_field(json::JsonValue& json,
                                     const std::string& key,
                                     const std::optional<models::Whitelisted>& in_field) {
    if (in_field.has_value()) {
        json::JsonValue value = json::JsonValue::create_string();
        value.try_set_string(EnumUtils::serialize_whitelisted(in_field.value()));

        json.try_set_object_field(key, value);
        return true;
    }

    json.try_remove_object_field(key);
    return false;
}

}

#endif //ENJINSDK_JSONUTILS_HPP
