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

#include "enjinsdk/JsonValue.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <utility>

using namespace enjin::sdk::json;
using namespace rapidjson;

class JsonValue::Impl final {
public:
    Impl() = delete;

    explicit Impl(Type type) : document(std::make_unique<Document>(type)) {
    }

    Impl(const Impl& other) {
        const Type type = other.document->GetType();

        document = std::make_unique<Document>(type);
        document->CopyFrom(*other.document, document->GetAllocator());
    }

    Impl(Impl&&) = default;

    ~Impl() = default;

    [[nodiscard]] std::set<std::string> get_object_field_keys() const {
        std::set<std::string> keys;

        if (is_object()) {
            for (const auto& member: document->GetObject()) {
                std::string key(member.name.GetString());
                keys.emplace(std::move(key));
            }
        }

        return keys;
    }

    [[nodiscard]] bool has_object_field(const std::string& key) const {
        return is_object() && document->HasMember(key.c_str());
    }

    [[nodiscard]] bool is_array() const {
        return document->IsArray();
    }

    [[nodiscard]] bool is_bool() const {
        return document->IsBool();
    }

    [[nodiscard]] bool is_double() const {
        return document->IsDouble();
    }

    [[nodiscard]] bool is_float() const {
        return document->IsFloat();
    }

    [[nodiscard]] bool is_int() const {
        return document->IsInt();
    }

    [[nodiscard]] bool is_int64() const {
        return document->IsInt64();
    }

    [[nodiscard]] bool is_null() const {
        return document->IsNull();
    }

    [[nodiscard]] bool is_number() const {
        return document->IsNumber();
    }

    [[nodiscard]] bool is_object() const {
        return document->IsObject();
    }

    [[nodiscard]] bool is_string() const {
        return document->IsString();
    }

    [[nodiscard]] std::string to_string() const {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document->Accept(writer);

        return {buffer.GetString()};
    }

    bool try_clear_array() {
        if (!is_array()) {
            return false;
        }

        document->Clear();
        return true;
    }

    bool try_clear_object() {
        if (!is_object()) {
            return false;
        }

        document->RemoveAllMembers();
        return true;
    }

    bool try_get_array(std::vector<JsonValue>& out) const {
        if (!is_array()) {
            return false;
        }

        out.clear();

        for (const auto& v: document->GetArray()) {
            switch (v.GetType()) {
                case kArrayType:
                    out.push_back(create_value_from_array(v));
                    break;

                case kFalseType:
                case kTrueType:
                    out.push_back(create_value_from_bool(v));
                    break;

                case kNullType:
                    out.push_back(JsonValue::create_null());
                    break;

                case kNumberType:
                    out.push_back(create_value_from_number(v));
                    break;

                case kObjectType:
                    out.push_back(create_value_from_object(v));
                    break;

                case kStringType:
                    out.push_back(create_value_from_string(v));
                    break;
            }
        }

        return true;
    }

    bool try_get_bool(bool& out) const {
        if (!is_bool()) {
            return false;
        }

        out = document->GetBool();
        return true;
    }

    bool try_get_number(double& out) const {
        if (!is_double()) {
            return false;
        }

        out = document->GetDouble();
        return true;
    }

    bool try_get_number(float& out) const {
        if (!is_float()) {
            return false;
        }

        out = document->GetFloat();
        return true;
    }

    bool try_get_number(int& out) const {
        if (!is_int()) {
            return false;
        }

        out = document->GetInt();
        return true;
    }

    bool try_get_number(int64_t& out) const {
        if (!is_int64()) {
            return false;
        }

        out = document->GetInt64();
        return true;
    }

    bool try_get_object_field(const std::string& key, JsonValue& out) const {
        if (!is_object()) {
            return false;
        }

        if (document->HasMember(key.c_str())) {
            Document& outDocument = *out.pimpl->document;
            const Value& v = document->operator[](key.c_str());

            outDocument.CopyFrom(v, outDocument.GetAllocator());
        } else {
            out.pimpl->document = std::make_unique<Document>(kNullType);
        }

        return true;
    }

    bool try_get_string(std::string& out) const {
        if (!is_string()) {
            return false;
        }

        out = std::string(document->GetString());
        return true;
    }

    bool try_parse_as_object(const std::string& raw) {
        Document new_document;

        new_document.Parse(raw.c_str());
        if (!new_document.IsObject()) {
            return false;
        }

        document->CopyFrom(new_document, document->GetAllocator());
        return true;
    }

    bool try_remove_object_field(const std::string& key) {
        if (!is_object()) {
            return false;
        }

        return document->RemoveMember(key.c_str());
    }

    bool try_set_array_element(const JsonValue& el) {
        if (!is_array()) {
            return false;
        }

        Document::AllocatorType& allocator = document->GetAllocator();

        Value v;
        v.CopyFrom(*el.pimpl->document, allocator);

        document->PushBack(v, allocator);
        return true;
    }

    bool try_set_bool(bool value) {
        if (!is_bool()) {
            return false;
        }

        document->SetBool(value);
        return true;
    }

    bool try_set_number(double value) {
        if (!is_double()) {
            return false;
        }

        document->SetDouble(value);
        return true;
    }

    bool try_set_number(float value) {
        if (!is_float()) {
            return false;
        }

        document->SetFloat(value);
        return true;
    }

    bool try_set_number(int value) {
        if (!is_int()) {
            return false;
        }

        document->SetInt(value);
        return true;
    }

    bool try_set_number(int64_t value) {
        if (!is_int64()) {
            return false;
        }

        document->SetInt64(value);
        return true;
    }

    bool try_set_object_field(const std::string& key, const JsonValue& value) {
        if (!is_object()) {
            return false;
        }

        Document::AllocatorType& allocator = document->GetAllocator();

        if (document->HasMember(key.c_str())) {
            document->RemoveMember(key.c_str());
        }

        Value k(key.c_str(), allocator);
        Value v;
        v.CopyFrom(*value.pimpl->document, allocator);

        document->AddMember(std::move(k), std::move(v), allocator);
        return true;
    }

    bool try_set_string(const std::string& value) {
        if (!is_string()) {
            return false;
        }

        document->SetString(value.c_str(), document->GetAllocator());
        return true;
    }

    bool operator==(const Impl& rhs) const {
        return *document == *rhs.document;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

    Impl& operator=(const Impl& rhs) {
        const Type type = rhs.document->GetType();

        document = std::make_unique<Document>(type);
        document->CopyFrom(*rhs.document, document->GetAllocator());

        return *this;
    }

private:
    std::unique_ptr<Document> document;

    static JsonValue create_value_from_array(const Value& value) {
        JsonValue json_value = JsonValue::create_array();

        Document& document = *json_value.pimpl->document;
        document.CopyFrom(value, document.GetAllocator());
        return json_value;
    }

    static JsonValue create_value_from_bool(const Value& value) {
        JsonValue json_value = JsonValue::create_bool();

        Document& document = *json_value.pimpl->document;
        document.CopyFrom(value, document.GetAllocator());
        return json_value;
    }

    static JsonValue create_value_from_number(const Value& value) {
        JsonValue json_value = JsonValue::create_number();

        Document& document = *json_value.pimpl->document;
        document.CopyFrom(value, document.GetAllocator());
        return json_value;
    }

    static JsonValue create_value_from_object(const Value& value) {
        JsonValue json_value = JsonValue::create_object();

        Document& document = *json_value.pimpl->document;
        document.CopyFrom(value, document.GetAllocator());
        return json_value;
    }

    static JsonValue create_value_from_string(const Value& value) {
        JsonValue json_value = JsonValue::create_string();

        Document& document = *json_value.pimpl->document;
        document.CopyFrom(value, document.GetAllocator());
        return json_value;
    }
};

JsonValue::JsonValue() : pimpl(std::make_unique<Impl>(kNullType)) {
}

JsonValue::JsonValue(std::unique_ptr<Impl> ptr) : pimpl(std::move(ptr)) {
}

JsonValue::JsonValue(const JsonValue& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

JsonValue::JsonValue(JsonValue&& other) noexcept = default;

JsonValue::~JsonValue() = default;

std::set<std::string> JsonValue::get_object_field_keys() const {
    return pimpl->get_object_field_keys();
}

bool JsonValue::has_object_field(const std::string& key) const {
    return pimpl->has_object_field(key);
}

bool JsonValue::is_array() const {
    return pimpl->is_array();
}

bool JsonValue::is_bool() const {
    return pimpl->is_bool();
}

bool JsonValue::is_double() const {
    return pimpl->is_double();
}

bool JsonValue::is_float() const {
    return pimpl->is_float();
}

bool JsonValue::is_int() const {
    return pimpl->is_int();
}

bool JsonValue::is_int64() const {
    return pimpl->is_int64();
}

bool JsonValue::is_null() const {
    return pimpl->is_null();
}

bool JsonValue::is_number() const {
    return pimpl->is_number();
}

bool JsonValue::is_object() const {
    return pimpl->is_object();
}

bool JsonValue::is_string() const {
    return pimpl->is_string();
}

std::string JsonValue::to_string() const {
    return pimpl->to_string();
}

bool JsonValue::try_clear_array() {
    return pimpl->try_clear_array();
}

bool JsonValue::try_clear_object() {
    return pimpl->try_clear_object();
}

bool JsonValue::try_get_array(std::vector<JsonValue>& out) const {
    return pimpl->try_get_array(out);
}

bool JsonValue::try_get_bool(bool& out) const {
    return pimpl->try_get_bool(out);
}

bool JsonValue::try_get_number(double& out) const {
    return pimpl->try_get_number(out);
}

bool JsonValue::try_get_number(float& out) const {
    return pimpl->try_get_number(out);
}

bool JsonValue::try_get_number(int& out) const {
    return pimpl->try_get_number(out);
}

bool JsonValue::try_get_number(int64_t& out) const {
    return pimpl->try_get_number(out);
}

bool JsonValue::try_get_object_field(const std::string& key, JsonValue& out) const {
    return pimpl->try_get_object_field(key, out);
}

bool JsonValue::try_remove_object_field(const std::string& key) {
    return pimpl->try_remove_object_field(key);
}

bool JsonValue::try_get_string(std::string& out) const {
    return pimpl->try_get_string(out);
}

bool JsonValue::try_parse_as_object(const std::string& raw) {
    return pimpl->try_parse_as_object(raw);
}

bool JsonValue::try_set_array_element(const JsonValue& el) {
    return pimpl->try_set_array_element(el);
}

bool JsonValue::try_set_bool(bool value) {
    return pimpl->try_set_bool(value);
}

bool JsonValue::try_set_number(double value) {
    return pimpl->try_set_number(value);
}

bool JsonValue::try_set_number(float value) {
    return pimpl->try_set_number(value);
}

bool JsonValue::try_set_number(int value) {
    return pimpl->try_set_number(value);
}

bool JsonValue::try_set_number(int64_t value) {
    return pimpl->try_set_number(value);
}

bool JsonValue::try_set_object_field(const std::string& key, const JsonValue& value) {
    return pimpl->try_set_object_field(key, value);
}

bool JsonValue::try_set_string(const std::string& value) {
    return pimpl->try_set_string(value);
}

bool JsonValue::operator==(const JsonValue& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool JsonValue::operator!=(const JsonValue& rhs) const {
    return !(*this == rhs);
}

JsonValue& JsonValue::operator=(const JsonValue& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}

JsonValue JsonValue::create_array() {
    return JsonValue(std::make_unique<Impl>(kArrayType));
}

JsonValue JsonValue::create_bool() {
    return JsonValue(std::make_unique<Impl>(kFalseType));
}

JsonValue JsonValue::create_null() {
    return JsonValue(std::make_unique<Impl>(kNullType));
}

JsonValue JsonValue::create_number() {
    return JsonValue(std::make_unique<Impl>(kNumberType));
}

JsonValue JsonValue::create_object() {
    return JsonValue(std::make_unique<Impl>(kObjectType));
}

JsonValue JsonValue::create_string() {
    return JsonValue(std::make_unique<Impl>(kStringType));
}
