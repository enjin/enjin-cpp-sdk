/* Copyright 2021 Enjin Pte Ltd.
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

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void AssetVariant::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsInt()) {
            id.emplace(document[ID_KEY].GetInt());
        }
        if (document.HasMember(ASSET_ID_KEY) && document[ASSET_ID_KEY].IsString()) {
            asset_id.emplace(document[ASSET_ID_KEY].GetString());
        }
        if (document.HasMember(VARIANT_METADATA_KEY) && document[VARIANT_METADATA_KEY].IsString()) {
            variant_metadata.emplace(document[VARIANT_METADATA_KEY].GetString());
        }
        if (document.HasMember(USAGE_COUNT_KEY) && document[USAGE_COUNT_KEY].IsInt()) {
            usage_count.emplace(document[USAGE_COUNT_KEY].GetInt());
        }
        if (document.HasMember(CREATED_AT_KEY) && document[CREATED_AT_KEY].IsString()) {
            created_at.emplace(document[CREATED_AT_KEY].GetString());
        }
        if (document.HasMember(UPDATED_AT_KEY) && document[UPDATED_AT_KEY].IsString()) {
            updated_at.emplace(document[UPDATED_AT_KEY].GetString());
        }
    }
}

const std::optional<int>& AssetVariant::get_id() const {
    return id;
}

const std::optional<std::string>& AssetVariant::get_asset_id() const {
    return asset_id;
}

const std::optional<std::string>& AssetVariant::get_variant_metadata() const {
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
    return id == rhs.id &&
           asset_id == rhs.asset_id &&
           variant_metadata == rhs.variant_metadata &&
           usage_count == rhs.usage_count &&
           created_at == rhs.created_at &&
           updated_at == rhs.updated_at;
}

bool AssetVariant::operator!=(const AssetVariant& rhs) const {
    return !(rhs == *this);
}

}
