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

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::utils;

void JsonUtils::join_object(JsonValue& json, const JsonValue& other) {
    if (!json.is_object() || !other.is_object()) {
        return;
    }

    for (const std::string& key: other.get_object_field_keys()) {
        JsonValue value;

        if (other.try_get_object_field(key, value)) {
            json.try_set_object_field(key, value);
        }
    }
}
