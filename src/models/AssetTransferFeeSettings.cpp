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

#include "enjinsdk/models/AssetTransferFeeSettings.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void AssetTransferFeeSettings::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        type.reset();
        asset_id.reset();
        value.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "type", type);
    JsonUtils::try_get_field(json_object, "assetId", asset_id);
    JsonUtils::try_get_field(json_object, "value", value);
}

const std::optional<AssetTransferFeeType>& AssetTransferFeeSettings::get_type() const {
    return type;
}

const std::optional<std::string>& AssetTransferFeeSettings::get_asset_id() const {
    return asset_id;
}

const std::optional<std::string>& AssetTransferFeeSettings::get_value() const {
    return value;
}

bool AssetTransferFeeSettings::operator==(const AssetTransferFeeSettings& rhs) const {
    return type == rhs.type
           && asset_id == rhs.asset_id
           && value == rhs.value;
}

bool AssetTransferFeeSettings::operator!=(const AssetTransferFeeSettings& rhs) const {
    return !(*this == rhs);
}
