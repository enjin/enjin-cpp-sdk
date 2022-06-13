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

#include "enjinsdk/models/Asset.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Asset::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            id.reset();
            name.reset();
            state_data.reset();
            config_data.reset();
            variant_mode.reset();
            variants.reset();
            created_at.reset();
            updated_at.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "id", id);
        JsonUtils::try_get_field(json_object, "name", name);
        JsonUtils::try_get_field(json_object, "stateData", state_data);
        JsonUtils::try_get_field(json_object, "configData", config_data);
        JsonUtils::try_get_field(json_object, "variantMode", variant_mode);
        JsonUtils::try_get_field(json_object, "variants", variants);
        JsonUtils::try_get_field(json_object, "createdAt", created_at);
        JsonUtils::try_get_field(json_object, "updatedAt", updated_at);
    }

    [[nodiscard]] const std::optional<std::string>& get_id() const {
        return id;
    }

    [[nodiscard]] const std::optional<std::string>& get_name() const {
        return name;
    }

    [[nodiscard]] const std::optional<AssetStateData>& get_state_data() const {
        return state_data;
    }

    [[nodiscard]] const std::optional<AssetConfigData>& get_config_data() const {
        return config_data;
    }

    [[nodiscard]] const std::optional<AssetVariantMode>& get_variant_mode() const {
        return variant_mode;
    }

    [[nodiscard]] const std::optional<std::vector<AssetVariant>>& get_variants() const {
        return variants;
    }

    [[nodiscard]] const std::optional<std::string>& get_created_at() const {
        return created_at;
    }

    [[nodiscard]] const std::optional<std::string>& get_updated_at() const {
        return updated_at;
    }

    bool operator==(const Impl& rhs) const {
        return id == rhs.id
               && name == rhs.name
               && state_data == rhs.state_data
               && config_data == rhs.config_data
               && variant_mode == rhs.variant_mode
               && variants == rhs.variants
               && created_at == rhs.created_at
               && updated_at == rhs.updated_at;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::optional<AssetStateData> state_data;
    std::optional<AssetConfigData> config_data;
    std::optional<AssetVariantMode> variant_mode;
    std::optional<std::vector<AssetVariant>> variants;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;
};

Asset::Asset() : pimpl(std::make_unique<Impl>()) {
}

Asset::Asset(const Asset& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

Asset::Asset(Asset&& other) noexcept = default;

Asset::~Asset() = default;

void Asset::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& Asset::get_id() const {
    return pimpl->get_id();
}

const std::optional<std::string>& Asset::get_name() const {
    return pimpl->get_name();
}

const std::optional<AssetStateData>& Asset::get_state_data() const {
    return pimpl->get_state_data();
}

const std::optional<AssetConfigData>& Asset::get_config_data() const {
    return pimpl->get_config_data();
}

const std::optional<AssetVariantMode>& Asset::get_variant_mode() const {
    return pimpl->get_variant_mode();
}

const std::optional<std::vector<AssetVariant>>& Asset::get_variants() const {
    return pimpl->get_variants();
}

const std::optional<std::string>& Asset::get_created_at() const {
    return pimpl->get_created_at();
}

const std::optional<std::string>& Asset::get_updated_at() const {
    return pimpl->get_updated_at();
}

bool Asset::operator==(const Asset& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool Asset::operator!=(const Asset& rhs) const {
    return *pimpl != *rhs.pimpl;
}

Asset& Asset::operator=(const Asset& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
