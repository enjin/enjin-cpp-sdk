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

#if _WIN32
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#endif

#include "enjinsdk/GraphqlError.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::graphql {

void GraphqlError::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(MESSAGE_KEY) && document[MESSAGE_KEY].IsString()) {
            message.emplace(document[MESSAGE_KEY].GetString());
        }
        if (document.HasMember(CODE_KEY) && document[CODE_KEY].IsInt()) {
            code.emplace(document[CODE_KEY].GetInt());
        }
        if (document.HasMember(DETAILS_KEY) && document[DETAILS_KEY].IsString()) {
            details.emplace(document[DETAILS_KEY].GetString());
        }
        if (document.HasMember(LOCATIONS_KEY) && document[LOCATIONS_KEY].IsArray()) {
            locations.emplace(std::vector<std::map<std::string, int>>());

            for (auto& l : document[LOCATIONS_KEY].GetArray()) {
                if (!l.IsObject()) {
                    continue;
                }

                std::map<std::string, int> location;
                for (auto& m : l.GetObject()) {
                    location[m.name.GetString()] = m.value.GetInt();
                }
                locations.value().emplace_back(location);
            }
        }
    }
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
    return message == rhs.message &&
           code == rhs.code &&
           locations == rhs.locations &&
           details == rhs.details;
}

bool GraphqlError::operator!=(const GraphqlError& rhs) const {
    return !(rhs == *this);
}

}
