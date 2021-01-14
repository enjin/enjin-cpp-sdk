#include "enjinsdk/models/Project.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void Project::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsInt()) {
            id.emplace(document[ID_KEY].GetInt());
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

const std::optional<int>& Project::get_id() const {
    return id;
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
    return id == rhs.id &&
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
