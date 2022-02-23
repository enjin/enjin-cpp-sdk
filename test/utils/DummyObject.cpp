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

#include "DummyObject.hpp"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

namespace enjin::test::utils {

DummyObject::DummyObject(int id) {
    this->id = std::optional<int>(id);
}

void DummyObject::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsInt()) {
            id = std::optional<int>(document[ID_KEY].GetInt());
        }
    }
}

std::string DummyObject::serialize() const {
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    if (id.has_value()) {
        rapidjson::Value v(id.value());
        document.AddMember(ID_KEY, v, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer <rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    const char* json = buffer.GetString();

    return std::string(json);
}

bool DummyObject::operator==(const DummyObject& rhs) const {
    return id == rhs.id;
}

bool DummyObject::operator!=(const DummyObject& rhs) const {
    return !(rhs == *this);
}

DummyObject DummyObject::create_default_dummy_object() {
    return DummyObject(1);
}

}
