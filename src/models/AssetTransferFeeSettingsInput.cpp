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

#include "RapidJsonUtils.hpp"
#include "enjinsdk/EnumUtils.hpp"
#include <utility>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

std::string AssetTransferFeeSettingsInput::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (type.has_value()) {
        set_string_member(document, TYPE_KEY, EnumUtils::serialize_asset_transfer_fee_type(type.value()));
    }

    if (asset_id.has_value()) {
        set_string_member(document, ASSET_ID_KEY, asset_id.value());
    }

    if (value.has_value()) {
        set_string_member(document, VALUE_KEY, value.value());
    }

    return document_to_string(document);
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_type(AssetTransferFeeType type) {
    AssetTransferFeeSettingsInput::type = type;
    return *this;
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_asset_id(std::string asset_id) {
    AssetTransferFeeSettingsInput::asset_id = std::move(asset_id);
    return *this;
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_value(std::string value) {
    AssetTransferFeeSettingsInput::value = std::move(value);
    return *this;
}

bool AssetTransferFeeSettingsInput::operator==(const AssetTransferFeeSettingsInput& rhs) const {
    return type == rhs.type
           && asset_id == rhs.asset_id
           && value == rhs.value;
}

bool AssetTransferFeeSettingsInput::operator!=(const AssetTransferFeeSettingsInput& rhs) const {
    return !(rhs == *this);
}
