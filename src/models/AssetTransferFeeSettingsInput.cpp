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

#include "enjinsdk/models/AssetTransferFeeSettingsInput.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

std::string AssetTransferFeeSettingsInput::serialize() const {
    return to_json().to_string();
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_type(AssetTransferFeeType type) {
    AssetTransferFeeSettingsInput::type_opt = type;
    return *this;
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_asset_id(std::string asset_id) {
    AssetTransferFeeSettingsInput::asset_id_opt = std::move(asset_id);
    return *this;
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_value(std::string value) {
    AssetTransferFeeSettingsInput::value_opt = std::move(value);
    return *this;
}

JsonValue AssetTransferFeeSettingsInput::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::try_set_field(json, "type", type_opt);
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "value", value_opt);

    return json;
}

bool AssetTransferFeeSettingsInput::operator==(const AssetTransferFeeSettingsInput& rhs) const {
    return type_opt == rhs.type_opt
           && asset_id_opt == rhs.asset_id_opt
           && value_opt == rhs.value_opt;
}

bool AssetTransferFeeSettingsInput::operator!=(const AssetTransferFeeSettingsInput& rhs) const {
    return !(*this == rhs);
}
