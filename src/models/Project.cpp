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
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Project::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
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

    [[nodiscard]] const std::optional<std::string>& get_uuid() const {
        return uuid;
    }

    [[nodiscard]] const std::optional<std::string>& get_name() const {
        return name;
    }

    [[nodiscard]] const std::optional<std::string>& get_description() const {
        return description;
    }

    [[nodiscard]] const std::optional<std::string>& get_image() const {
        return image;
    }

    [[nodiscard]] const std::optional<std::string>& get_created_at() const {
        return created_at;
    }

    [[nodiscard]] const std::optional<std::string>& get_updated_at() const {
        return updated_at;
    }

    bool operator==(const Impl& rhs) const {
        return uuid == rhs.uuid
               && name == rhs.name
               && description == rhs.description
               && image == rhs.image
               && created_at == rhs.created_at
               && updated_at == rhs.updated_at;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> uuid;
    std::optional<std::string> name;
    std::optional<std::string> description;
    std::optional<std::string> image;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;
};

Project::Project() : pimpl(std::make_unique<Impl>()) {
}

Project::Project(const Project& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

Project::Project(Project&& other) noexcept = default;

Project::~Project() = default;

void Project::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& Project::get_uuid() const {
    return pimpl->get_uuid();
}

const std::optional<std::string>& Project::get_name() const {
    return pimpl->get_name();
}

const std::optional<std::string>& Project::get_description() const {
    return pimpl->get_description();
}

const std::optional<std::string>& Project::get_image() const {
    return pimpl->get_image();
}

const std::optional<std::string>& Project::get_created_at() const {
    return pimpl->get_created_at();
}

const std::optional<std::string>& Project::get_updated_at() const {
    return pimpl->get_updated_at();
}

bool Project::operator==(const Project& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool Project::operator!=(const Project& rhs) const {
    return *pimpl != *rhs.pimpl;
}

Project& Project::operator=(const Project& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
