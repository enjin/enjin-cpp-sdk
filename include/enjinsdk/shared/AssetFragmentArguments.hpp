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

#ifndef ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include <optional>
#include <string>
#include <type_traits>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from assets returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT AssetFragmentArguments : public serialization::ISerializable {
public:
    ~AssetFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    /// \brief Sets the desired asset ID format.
    /// \param asset_id_format The format.
    /// \return This request for chaining.
    T& set_asset_id_format(models::AssetIdFormat asset_id_format) {
        asset_id_format_opt = asset_id_format;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the state data with the asset.
    /// \return This request for chaining.
    T& set_with_state_data() {
        with_state_data_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the configuration data with the asset.
    /// \return This request for chaining.
    T& set_with_config_data() {
        with_config_data_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the block data with the asset when used with set_with_state_data().
    /// \return This request for chaining.
    T& set_with_asset_blocks() {
        with_asset_blocks_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the creator with the asset when used with set_with_state_data().
    /// \return This request for chaining.
    T& set_with_creator() {
        with_creator_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the melt details with the asset when used with set_with_config_data().
    /// \return This request for chaining.
    T& set_with_melt_details() {
        with_melt_details_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata URI with the asset when used with set_with_config_data().
    /// \return This request for chaining.
    T& set_with_metadata_uri() {
        with_metadata_uri_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the supply details with the asset when used with
    /// set_with_state_data().
    /// \return This request for chaining.
    T& set_with_supply_details() {
        with_supply_details_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the transfer settings with the asset when used with
    /// set_with_config_data().
    /// \return This request for chaining.
    T& set_with_transfer_settings() {
        with_transfer_settings_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variant mode with the asset.
    /// \return This request for chaining.
    T& set_with_asset_variant_mode() {
        with_asset_variant_mode_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variants with the asset.
    /// \return This request for chaining.
    T& set_with_asset_variants() {
        with_asset_variants_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata for the variants with the asset when used with
    /// set_with_asset_variants().
    /// \return This request for chaining.
    T& set_with_variant_metadata() {
        with_variant_metadata_opt = true;
        return static_cast<T&>(*this);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        json::JsonValue json = json::JsonValue::create_object();

        utils::JsonUtils::try_set_field(json, "assetIdFormat", asset_id_format_opt);
        utils::JsonUtils::try_set_field(json, "withStateData", with_state_data_opt);
        utils::JsonUtils::try_set_field(json, "withConfigData", with_config_data_opt);
        utils::JsonUtils::try_set_field(json, "withAssetBlocks", with_asset_blocks_opt);
        utils::JsonUtils::try_set_field(json, "withCreator", with_creator_opt);
        utils::JsonUtils::try_set_field(json, "withMeltDetails", with_melt_details_opt);
        utils::JsonUtils::try_set_field(json, "withMetadataURI", with_metadata_uri_opt);
        utils::JsonUtils::try_set_field(json, "withSupplyDetails", with_supply_details_opt);
        utils::JsonUtils::try_set_field(json, "withTransferSettings", with_transfer_settings_opt);
        utils::JsonUtils::try_set_field(json, "withAssetVariantMode", with_asset_variant_mode_opt);
        utils::JsonUtils::try_set_field(json, "withAssetVariants", with_asset_variants_opt);
        utils::JsonUtils::try_set_field(json, "withVariantMetadata", with_variant_metadata_opt);

        return json;
    }

    bool operator==(const AssetFragmentArguments& rhs) const {
        return asset_id_format_opt == rhs.asset_id_format_opt
               && with_state_data_opt == rhs.with_state_data_opt
               && with_config_data_opt == rhs.with_config_data_opt
               && with_asset_blocks_opt == rhs.with_asset_blocks_opt
               && with_creator_opt == rhs.with_creator_opt
               && with_melt_details_opt == rhs.with_melt_details_opt
               && with_metadata_uri_opt == rhs.with_metadata_uri_opt
               && with_supply_details_opt == rhs.with_supply_details_opt
               && with_transfer_settings_opt == rhs.with_transfer_settings_opt
               && with_asset_variant_mode_opt == rhs.with_asset_variant_mode_opt
               && with_asset_variants_opt == rhs.with_asset_variants_opt
               && with_variant_metadata_opt == rhs.with_variant_metadata_opt;
    }

    bool operator!=(const AssetFragmentArguments& rhs) const {
        return !(*this == rhs);
    }

protected:
    /// \brief Sole constructor.
    AssetFragmentArguments() {
        static_assert(std::is_base_of<AssetFragmentArguments, T>::value,
                      "Class T does not inherit from AssetFragmentArguments.");
    }

private:
    std::optional<models::AssetIdFormat> asset_id_format_opt;
    std::optional<bool> with_state_data_opt;
    std::optional<bool> with_config_data_opt;
    std::optional<bool> with_asset_blocks_opt;
    std::optional<bool> with_creator_opt;
    std::optional<bool> with_melt_details_opt;
    std::optional<bool> with_metadata_uri_opt;
    std::optional<bool> with_supply_details_opt;
    std::optional<bool> with_transfer_settings_opt;
    std::optional<bool> with_asset_variant_mode_opt;
    std::optional<bool> with_asset_variants_opt;
    std::optional<bool> with_variant_metadata_opt;
};

}

#endif //ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP
