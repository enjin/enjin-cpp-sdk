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

#include "RapidJsonUtils.hpp"

#include <stdexcept>

namespace enjin::sdk::utils {

void join_serialized_object_to_document(rapidjson::Document& document,
                                        const std::string& o) {
    if (!document.IsObject()) {
        throw std::runtime_error("Document is not a Json Object");
    }

    rapidjson::Document object_document;
    object_document.Parse(o.c_str());

    if (!object_document.IsObject()) {
        return;
    }

    auto& allocator = document.GetAllocator();
    for (auto& [key, value] : object_document.GetObject()) {
        rapidjson::Value v_key;
        v_key.SetString(key.GetString(), allocator);
        document.AddMember(v_key, value, allocator);
    }
}

void join_serialized_objects_to_document(rapidjson::Document& document,
                                         const std::vector<std::string>& o) {
    if (!document.IsObject()) {
        throw std::runtime_error("Document is not a Json Object");
    }

    for (const auto& s : o) {
        join_serialized_object_to_document(document, s);
    }
}

std::string document_to_string(const rapidjson::Document& document) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return std::string(buffer.GetString());
}

std::vector<std::string> get_array_as_serialized_vector(const rapidjson::Document& document, const std::string& key) {
    if (key.empty() && document.IsArray()) {
        std::vector<std::string> v;
        for (auto& arr_el : document.GetArray()) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            arr_el.Accept(writer);
            v.emplace_back(buffer.GetString());
        }
        return v;
    } else if (!key.empty() && document[key.c_str()].IsArray()) {
        std::vector<std::string> v;
        for (auto& arr_el : document[key.c_str()].GetArray()) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            arr_el.Accept(writer);
            v.emplace_back(buffer.GetString());
        }
        return v;
    }

    throw std::runtime_error("JSON element is not an array");
}

std::string get_object_as_string(const rapidjson::Document& document, const std::string& key) {
    if (key.empty() && document.IsObject()) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        return buffer.GetString();
    } else if (!key.empty() && document[key.c_str()].IsObject()) {
        auto& v_value = document[key.c_str()];
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        v_value.Accept(writer);
        return buffer.GetString();
    }

    throw std::runtime_error("JSON element is not an object");
}

void set_member_assert(const rapidjson::Document& document, const std::string& key) {
    if (!document.IsObject()) {
        throw std::runtime_error("Document is not a Json Object");
    } else if (key.empty()) {
        throw std::runtime_error("Key string is empty");
    }
}

void set_array_member_from_string_vector(rapidjson::Document& document,
                                         const std::string& key,
                                         const std::vector<std::string>& values) {
    set_member_assert(document, key);

    auto& allocator = document.GetAllocator();
    rapidjson::Value v(rapidjson::kArrayType);
    for (auto& e : values) {
        rapidjson::Value e_value;
        e_value.SetString(e.c_str(), allocator);
        v.PushBack(e_value, allocator);
    }

    rapidjson::Value v_key;
    v_key.SetString(key.c_str(), allocator);
    document.AddMember(v_key, v, allocator);
}

void set_boolean_member(rapidjson::Document& document, const std::string& key, bool value) {
    set_member_assert(document, key);

    auto& allocator = document.GetAllocator();
    rapidjson::Value v_key;
    rapidjson::Value v;
    v_key.SetString(key.c_str(), allocator);
    v.SetBool(value);
    document.AddMember(v_key, v, allocator);
}

void set_integer_member(rapidjson::Document& document, const std::string& key, int value) {
    set_member_assert(document, key);

    auto& allocator = document.GetAllocator();
    rapidjson::Value v_key;
    rapidjson::Value v;
    v_key.SetString(key.c_str(), allocator);
    v.SetInt(value);
    document.AddMember(v_key, v, allocator);
}

void set_string_member(rapidjson::Document& document, const std::string& key, const std::string& value) {
    set_member_assert(document, key);

    auto& allocator = document.GetAllocator();
    rapidjson::Value v_key;
    rapidjson::Value v;
    v_key.SetString(key.c_str(), allocator);
    v.SetString(value.c_str(), allocator);
    document.AddMember(v_key, v, allocator);
}

void set_object_member_from_string(rapidjson::Document& document, const std::string& key, const std::string& value) {
    set_member_assert(document, key);

    /* Opens value as a JSON document to dynamically acquire its member name and values to convert into a JSON object
     * that may then be stored.
     */
    rapidjson::Document e_document;
    e_document.Parse(value.c_str());

    if (!e_document.IsObject()) {
        return;
    }

    auto& allocator = document.GetAllocator();
    rapidjson::Value v_key;
    rapidjson::Value v(e_document, allocator);
    v_key.SetString(key.c_str(), allocator);
    document.AddMember(v_key, v, allocator);
}

}
