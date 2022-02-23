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

#include "enjinsdk/models/Project.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void Project::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(UUID_KEY) && document[UUID_KEY].IsString()) {
            uuid.emplace(document[UUID_KEY].GetString());
        }
        if (document.HasMember(NAME_KEY) && document[NAME_KEY].IsString()) {
            name.emplace(document[NAME_KEY].GetString());
        }
        if (document.HasMember(DESCRIPTION_KEY) && document[DESCRIPTION_KEY].IsString()) {
            description.emplace(document[DESCRIPTION_KEY].GetString());
        }
        if (document.HasMember(IMAGE_KEY) && document[IMAGE_KEY].IsString()) {
            image.emplace(document[IMAGE_KEY].GetString());
        }
        if (document.HasMember(CREATED_AT_KEY) && document[CREATED_AT_KEY].IsString()) {
            created_at.emplace(document[CREATED_AT_KEY].GetString());
        }
        if (document.HasMember(UPDATED_AT_KEY) && document[UPDATED_AT_KEY].IsString()) {
            updated_at.emplace(document[UPDATED_AT_KEY].GetString());
        }
    }
}

const std::optional<std::string>& Project::get_uuid() const {
    return uuid;
}

const std::optional<std::string>& Project::get_name() const {
    return name;
}

const std::optional<std::string>& Project::get_description() const {
    return description;
}

const std::optional<std::string>& Project::get_image() const {
    return image;
}

const std::optional<std::string>& Project::get_created_at() const {
    return created_at;
}

const std::optional<std::string>& Project::get_updated_at() const {
    return updated_at;
}

bool Project::operator==(const Project& rhs) const {
    return uuid == rhs.uuid &&
           name == rhs.name &&
           description == rhs.description &&
           image == rhs.image &&
           created_at == rhs.created_at &&
           updated_at == rhs.updated_at;
}

bool Project::operator!=(const Project& rhs) const {
    return !(rhs == *this);
}

}
