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

#include "enjinsdk/models/AssetTransferFeeSettings.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void AssetTransferFeeSettings::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(TYPE_KEY) && document[TYPE_KEY].IsString()) {
            type.emplace(utils::deserialize_asset_transfer_fee_type(document[TYPE_KEY].GetString()));
        }
        if (document.HasMember(ASSET_ID_KEY) && document[ASSET_ID_KEY].IsString()) {
            asset_id.emplace(document[ASSET_ID_KEY].GetString());
        }
        if (document.HasMember(VALUE_KEY) && document[VALUE_KEY].IsString()) {
            value.emplace(document[VALUE_KEY].GetString());
        }
    }
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
    return type == rhs.type &&
           asset_id == rhs.asset_id &&
           value == rhs.value;
}

bool AssetTransferFeeSettings::operator!=(const AssetTransferFeeSettings& rhs) const {
    return !(rhs == *this);
}

std::string AssetTransferFeeSettingsInput::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (type.has_value()) {
        utils::set_string_member(document, TYPE_KEY, utils::serialize_asset_transfer_fee_type(type.value()));
    }
    if (asset_id.has_value()) {
        utils::set_string_member(document, ASSET_ID_KEY, asset_id.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, VALUE_KEY, value.value());
    }

    return utils::document_to_string(document);
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_type(AssetTransferFeeType type) {
    AssetTransferFeeSettingsInput::type = type;
    return *this;
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_asset_id(const std::string& asset_id) {
    AssetTransferFeeSettingsInput::asset_id = asset_id;
    return *this;
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_value(const std::string& value) {
    AssetTransferFeeSettingsInput::value = value;
    return *this;
}

bool AssetTransferFeeSettingsInput::operator==(const AssetTransferFeeSettingsInput& rhs) const {
    return static_cast<const AssetTransferFeeSettings&>(*this) ==
           static_cast<const AssetTransferFeeSettings&>(rhs);
}

bool AssetTransferFeeSettingsInput::operator!=(const AssetTransferFeeSettingsInput& rhs) const {
    return !(rhs == *this);
}

}
