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

#include "enjinsdk/models//AssetConfigData.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void AssetConfigData::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        melt_fee_ratio.reset();
        melt_fee_max_ratio.reset();
        melt_value.reset();
        metadata_uri.reset();
        transferable.reset();
        transfer_fee_settings.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "meltFeeRatio", melt_fee_ratio);
    JsonUtils::try_get_field(json_object, "meltFeeMaxRatio", melt_fee_max_ratio);
    JsonUtils::try_get_field(json_object, "meltValue", melt_value);
    JsonUtils::try_get_field(json_object, "metadataURI", metadata_uri);
    JsonUtils::try_get_field(json_object, "transferable", transferable);
    JsonUtils::try_get_field(json_object, "transferFeeSettings", transfer_fee_settings);
}

const std::optional<int>& AssetConfigData::get_melt_fee_ratio() const {
    return melt_fee_ratio;
}

const std::optional<int>& AssetConfigData::get_melt_fee_max_ratio() const {
    return melt_fee_max_ratio;
}

const std::optional<std::string>& AssetConfigData::get_melt_value() const {
    return melt_value;
}

const std::optional<std::string>& AssetConfigData::get_metadata_uri() const {
    return metadata_uri;
}

const std::optional<AssetTransferable>& AssetConfigData::get_transferable() const {
    return transferable;
}

const std::optional<AssetTransferFeeSettings>& AssetConfigData::get_transfer_fee_settings() const {
    return transfer_fee_settings;
}

bool AssetConfigData::operator==(const AssetConfigData& rhs) const {
    return melt_fee_ratio == rhs.melt_fee_ratio
           && melt_fee_max_ratio == rhs.melt_fee_max_ratio
           && melt_value == rhs.melt_value
           && metadata_uri == rhs.metadata_uri
           && transferable == rhs.transferable
           && transfer_fee_settings == rhs.transfer_fee_settings;
}

bool AssetConfigData::operator!=(const AssetConfigData& rhs) const {
    return !(*this == rhs);
}
