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

#include "enjinsdk/models/Project.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void Project::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        uuid.reset();
        name.reset();
        description.reset();
        image.reset();
        created_at.reset();
        updated_at.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "uuid", uuid);
    JsonUtils::try_get_field(json_object, "name", name);
    JsonUtils::try_get_field(json_object, "description", description);
    JsonUtils::try_get_field(json_object, "image", image);
    JsonUtils::try_get_field(json_object, "createdAt", created_at);
    JsonUtils::try_get_field(json_object, "updatedAt", updated_at);
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
    return uuid == rhs.uuid
           && name == rhs.name
           && description == rhs.description
           && image == rhs.image
           && created_at == rhs.created_at
           && updated_at == rhs.updated_at;
}

bool Project::operator!=(const Project& rhs) const {
    return !(*this == rhs);
}
