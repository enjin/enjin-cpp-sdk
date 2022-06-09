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
using namespace enjin::sdk::utils;

void AssetVariant::deserialize(const std::string& json) {
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

const std::optional<int>& AssetVariant::get_id() const {
    return id;
}

const std::optional<std::string>& AssetVariant::get_asset_id() const {
    return asset_id;
}

const std::optional<JsonValue>& AssetVariant::get_variant_metadata() const {
    return variant_metadata;
}

const std::optional<int>& AssetVariant::get_usage_count() const {
    return usage_count;
}

const std::optional<std::string>& AssetVariant::get_created_at() const {
    return created_at;
}

const std::optional<std::string>& AssetVariant::get_updated_at() const {
    return updated_at;
}

bool AssetVariant::operator==(const AssetVariant& rhs) const {
    return id == rhs.id
           && asset_id == rhs.asset_id
           && variant_metadata == rhs.variant_metadata
           && usage_count == rhs.usage_count
           && created_at == rhs.created_at
           && updated_at == rhs.updated_at;
}

bool AssetVariant::operator!=(const AssetVariant& rhs) const {
    return !(*this == rhs);
}
