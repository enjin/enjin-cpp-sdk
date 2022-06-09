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

#include "enjinsdk/GraphqlError.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"
#include <map>
#include <set>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::utils;

void GraphqlError::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        message.reset();
        code.reset();
        locations.reset();
        details.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "message", message);
    JsonUtils::try_get_field(json_object, "code", code);
    JsonUtils::try_get_field(json_object, "message", details);

    JsonValue locations_field;
    std::vector<JsonValue> locations_value;
    if (!json_object.try_get_object_field("locations", locations_field)
        || !locations_field.try_get_array(locations_value)) {
        locations.reset();
        return;
    }

    std::vector<std::map<std::string, int>> locations_array;

    for (const JsonValue& location_value: locations_value) {
        std::map<std::string, int> location;
        std::set<std::string> keys = location_value.get_object_field_keys();

        for (const std::string& key: keys) {
            int value;
            JsonValue value_value;

            if (location_value.try_get_object_field(key, value_value) && value_value.try_get_number(value)) {
                location.emplace(key, value);
            }
        }

        locations_array.push_back(std::move(location));
    }

    locations.emplace(std::move(locations_array));
}

const std::optional<std::string>& GraphqlError::get_message() const {
    return message;
}

const std::optional<int>& GraphqlError::get_code() const {
    return code;
}

const std::optional<std::vector<std::map<std::string, int>>>& GraphqlError::get_locations() const {
    return locations;
}

const std::optional<std::string>& GraphqlError::get_details() const {
    return details;
}

bool GraphqlError::operator==(const GraphqlError& rhs) const {
    return message == rhs.message
           && code == rhs.code
           && locations == rhs.locations
           && details == rhs.details;
}

bool GraphqlError::operator!=(const GraphqlError& rhs) const {
    return !(*this == rhs);
}
