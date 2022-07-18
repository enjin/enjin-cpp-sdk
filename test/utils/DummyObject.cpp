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

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::utils;
using namespace enjin::test::utils;

DummyObject::DummyObject(int id) : id(std::optional<int>(id)) {
}

void DummyObject::deserialize(const std::string& json) {
    JsonValue json_value;
    if (!json_value.try_parse_as_object(json)) {
        id.reset();

        return;
    }

    JsonUtils::try_get_field(json_value, IdKey, id);
}

std::string DummyObject::serialize() const {
    return to_json().to_string();
}

JsonValue DummyObject::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::try_set_field(json, IdKey, id);

    return json;
}

bool DummyObject::operator==(const DummyObject& rhs) const {
    return id == rhs.id;
}

bool DummyObject::operator!=(const DummyObject& rhs) const {
    return !(*this == rhs);
}

DummyObject DummyObject::create_default_dummy_object() {
    return DummyObject(1);
}
