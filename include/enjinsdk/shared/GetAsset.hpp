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

#ifndef ENJINCPPSDK_SHAREDGETASSET_HPP
#define ENJINCPPSDK_SHAREDGETASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/AssetFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for getting a asset on the platform.
class ENJINSDK_EXPORT GetAsset : public graphql::AbstractGraphqlRequest,
                                 public AssetFragmentArguments<GetAsset> {
public:
    /// \brief Default constructor.
    GetAsset();

    ~GetAsset() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param id The ID.
    /// \return This request for chaining.
    GetAsset& set_id(std::string id);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const GetAsset& rhs) const;

    bool operator!=(const GetAsset& rhs) const;

private:
    std::optional<std::string> id_opt;
};

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_state_data();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_config_data();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_asset_blocks();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_creator();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_melt_details();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_metadata_uri();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_supply_details();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_transfer_settings();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_asset_variant_mode();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_asset_variants();

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_with_variant_metadata();

}

#endif //ENJINCPPSDK_SHAREDGETASSET_HPP
