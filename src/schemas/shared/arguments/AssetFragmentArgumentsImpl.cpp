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

#include "enjinsdk/internal/AssetFragmentArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"
#include "enjinsdk/EnumUtils.hpp"

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

std::string AssetFragmentArgumentsImpl::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (asset_id_format.has_value()) {
        set_string_member(document,
                          "assetIdFormat",
                          EnumUtils::serialize_asset_id_format(asset_id_format.value()));
    }
    if (with_state_data.has_value()) {
        set_boolean_member(document, "withStateData", with_state_data.value());
    }
    if (with_config_data.has_value()) {
        set_boolean_member(document, "withConfigData", with_config_data.value());
    }
    if (with_asset_blocks.has_value()) {
        set_boolean_member(document, "withAssetBlocks", with_asset_blocks.value());
    }
    if (with_creator.has_value()) {
        set_boolean_member(document, "withCreator", with_creator.value());
    }
    if (with_melt_details.has_value()) {
        set_boolean_member(document, "withMeltDetails", with_melt_details.value());
    }
    if (with_metadata_uri.has_value()) {
        set_boolean_member(document, "withMetadataURI", with_metadata_uri.value());
    }
    if (with_supply_details.has_value()) {
        set_boolean_member(document, "withSupplyDetails", with_supply_details.value());
    }
    if (with_transfer_settings.has_value()) {
        set_boolean_member(document, "withTransferSettings", with_transfer_settings.value());
    }
    if (with_asset_variant_mode.has_value()) {
        set_boolean_member(document, "withAssetVariantMode", with_asset_variant_mode.value());
    }
    if (with_asset_variants.has_value()) {
        set_boolean_member(document, "withAssetVariants", with_asset_variants.value());
    }
    if (with_variant_metadata.has_value()) {
        set_boolean_member(document, "withVariantMetadata", with_variant_metadata.value());
    }

    return document_to_string(document);
}

void AssetFragmentArgumentsImpl::set_asset_id_format(AssetIdFormat asset_id_format) {
    AssetFragmentArgumentsImpl::asset_id_format = asset_id_format;
}

void AssetFragmentArgumentsImpl::set_with_state_data() {
    with_state_data = true;
}

void AssetFragmentArgumentsImpl::set_with_config_data() {
    with_config_data = true;
}

void AssetFragmentArgumentsImpl::set_with_asset_blocks() {
    with_asset_blocks = true;
}

void AssetFragmentArgumentsImpl::set_with_creator() {
    with_creator = true;
}

void AssetFragmentArgumentsImpl::set_with_melt_details() {
    with_melt_details = true;
}

void AssetFragmentArgumentsImpl::set_with_metadata_uri() {
    with_metadata_uri = true;
}

void AssetFragmentArgumentsImpl::set_with_supply_details() {
    with_supply_details = true;
}

void AssetFragmentArgumentsImpl::set_with_transfer_settings() {
    with_transfer_settings = true;
}

void AssetFragmentArgumentsImpl::set_with_asset_variant_mode() {
    with_asset_variant_mode = true;
}

void AssetFragmentArgumentsImpl::set_with_asset_variants() {
    with_asset_variants = true;
}

void AssetFragmentArgumentsImpl::set_with_variant_metadata() {
    with_variant_metadata = true;
}

bool AssetFragmentArgumentsImpl::operator==(const AssetFragmentArgumentsImpl& rhs) const {
    return asset_id_format == rhs.asset_id_format
           && with_state_data == rhs.with_state_data
           && with_config_data == rhs.with_config_data
           && with_asset_blocks == rhs.with_asset_blocks
           && with_creator == rhs.with_creator
           && with_melt_details == rhs.with_melt_details
           && with_metadata_uri == rhs.with_metadata_uri
           && with_supply_details == rhs.with_supply_details
           && with_transfer_settings == rhs.with_transfer_settings
           && with_asset_variant_mode == rhs.with_asset_variant_mode
           && with_asset_variants == rhs.with_asset_variants
           && with_variant_metadata == rhs.with_variant_metadata;
}

bool AssetFragmentArgumentsImpl::operator!=(const AssetFragmentArgumentsImpl& rhs) const {
    return !(rhs == *this);
}
