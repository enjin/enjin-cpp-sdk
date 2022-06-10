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

#include "enjinsdk/models/AssetVariant.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class AssetVariant::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            id.reset();
            asset_id.reset();
            variant_metadata.reset();
            usage_count.reset();
            created_at.reset();
            updated_at.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "id", id);
        JsonUtils::try_get_field(json_object, "assetId", asset_id);
        JsonUtils::try_get_field(json_object, "variantMetadata", variant_metadata);
        JsonUtils::try_get_field(json_object, "usageCount", usage_count);
        JsonUtils::try_get_field(json_object, "createdAt", created_at);
        JsonUtils::try_get_field(json_object, "updatedAt", updated_at);
    }

    [[nodiscard]] const std::optional<int>& get_id() const {
        return id;
    }

    [[nodiscard]] const std::optional<std::string>& get_asset_id() const {
        return asset_id;
    }

    [[nodiscard]] const std::optional<json::JsonValue>& get_variant_metadata() const {
        return variant_metadata;
    }

    [[nodiscard]] const std::optional<int>& get_usage_count() const {
        return usage_count;
    }

    [[nodiscard]] const std::optional<std::string>& get_created_at() const {
        return created_at;
    }

    [[nodiscard]] const std::optional<std::string>& get_updated_at() const {
        return updated_at;
    }

    bool operator==(const Impl& rhs) const {
        return id == rhs.id
               && asset_id == rhs.asset_id
               && variant_metadata == rhs.variant_metadata
               && usage_count == rhs.usage_count
               && created_at == rhs.created_at
               && updated_at == rhs.updated_at;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<int> id;
    std::optional<std::string> asset_id;
    std::optional<json::JsonValue> variant_metadata;
    std::optional<int> usage_count;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;
};

AssetVariant::AssetVariant() : pimpl(std::make_unique<Impl>()) {
}

AssetVariant::AssetVariant(const AssetVariant& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

AssetVariant::AssetVariant(AssetVariant&& other) noexcept = default;

AssetVariant::~AssetVariant() = default;

void AssetVariant::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<int>& AssetVariant::get_id() const {
    return pimpl->get_id();
}

const std::optional<std::string>& AssetVariant::get_asset_id() const {
    return pimpl->get_asset_id();
}

const std::optional<JsonValue>& AssetVariant::get_variant_metadata() const {
    return pimpl->get_variant_metadata();
}

const std::optional<int>& AssetVariant::get_usage_count() const {
    return pimpl->get_usage_count();
}

const std::optional<std::string>& AssetVariant::get_created_at() const {
    return pimpl->get_created_at();
}

const std::optional<std::string>& AssetVariant::get_updated_at() const {
    return pimpl->get_updated_at();
}

bool AssetVariant::operator==(const AssetVariant& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool AssetVariant::operator!=(const AssetVariant& rhs) const {
    return *pimpl != *rhs.pimpl;
}

AssetVariant& AssetVariant::operator=(const AssetVariant& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
