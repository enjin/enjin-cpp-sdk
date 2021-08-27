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

#ifndef ENJINCPPSDK_RAPIDJSONUTILS_HPP
#define ENJINCPPSDK_RAPIDJSONUTILS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/ISerializable.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace enjin::sdk::utils {

ENJINSDK_EXPORT
void join_serialized_object_to_document(rapidjson::Document& document,
                                        const std::string& o);

ENJINSDK_EXPORT
void join_serialized_objects_to_document(rapidjson::Document& document,
                                         const std::vector<std::string>& o);

ENJINSDK_EXPORT
std::string document_to_string(const rapidjson::Document& document);

ENJINSDK_EXPORT
std::vector<std::string> get_array_as_serialized_vector(const rapidjson::Document& document,
                                                        const std::string& key = "");

template<class T>
std::vector<T> get_array_as_type_vector(const rapidjson::Document& document,
                                        const std::string& key = "") {
    static_assert(std::is_base_of<serialization::IDeserializable, T>::value,
                  "Class T does not inherit from IDeserializable.");

    if (key.empty() && document.IsArray()) {
        std::vector<T> v;
        for (auto& arr_el : document.GetArray()) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            arr_el.Accept(writer);
            T t;
            t.deserialize(buffer.GetString());
            v.push_back(t);
        }
        return v;
    } else if (!key.empty() && document[key.c_str()].IsArray()) {
        std::vector<T> v;
        for (auto& arr_el : document[key.c_str()].GetArray()) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            arr_el.Accept(writer);
            T t;
            t.deserialize(buffer.GetString());
            v.push_back(t);
        }
        return v;
    }

    throw std::runtime_error("JSON element is not an array");
}

ENJINSDK_EXPORT
std::string get_object_as_string(const rapidjson::Document& document, const std::string& key = "");

template<class T>
T get_object_as_type(const rapidjson::Document& document, const std::string& key = "") {
    static_assert(std::is_base_of<serialization::IDeserializable, T>::value,
                  "Class T does not inherit from IDeserializable.");

    T t;
    t.deserialize(get_object_as_string(document, key));
    return t;
}

ENJINSDK_EXPORT
void set_member_assert(const rapidjson::Document& document, const std::string& key);

template<class T>
void set_array_member_from_type_vector(rapidjson::Document& document,
                                       const std::string& key,
                                       std::vector<T> values) {
    static_assert(std::is_base_of<serialization::ISerializable, T>::value,
                  "Class T does not inherit from ISerializable.");

    set_member_assert(document, key);

    auto& allocator = document.GetAllocator();
    rapidjson::Value arr(rapidjson::kArrayType);

    for (auto& v : values) {
        rapidjson::Document v_document(&allocator);
        v_document.Parse(v.serialize().c_str());
        arr.PushBack(v_document, allocator);
    }

    rapidjson::Value arr_key;
    arr_key.SetString(key.c_str(), allocator);
    document.AddMember(arr_key, arr, allocator);
}

ENJINSDK_EXPORT
void set_array_member_from_string_vector(rapidjson::Document& document,
                                         const std::string& key,
                                         const std::vector<std::string>& values);

ENJINSDK_EXPORT
void set_boolean_member(rapidjson::Document& document, const std::string& key, bool value);

ENJINSDK_EXPORT
void set_integer_member(rapidjson::Document& document, const std::string& key, int value);

ENJINSDK_EXPORT
void set_string_member(rapidjson::Document& document, const std::string& key, const std::string& value);

ENJINSDK_EXPORT
void set_object_member_from_string(rapidjson::Document& document, const std::string& key, const std::string& value);

template<class T>
void set_object_member_from_type(rapidjson::Document& document,
                                 const std::string& key,
                                 T value) {
    static_assert(std::is_base_of<serialization::ISerializable, T>::value,
                  "Class T does not inherit from ISerializable.");

    set_object_member_from_string(document, key, value.serialize());
}

}

#endif //ENJINCPPSDK_RAPIDJSONUTILS_HPP
