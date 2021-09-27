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

#ifndef ENJINCPPSDK_SHAREDGETASSETS_HPP
#define ENJINCPPSDK_SHAREDGETASSETS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Asset.hpp"
#include "enjinsdk/models/AssetFilter.hpp"
#include "enjinsdk/models/AssetSort.hpp"
#include "enjinsdk/shared/PaginationArguments.hpp"
#include "enjinsdk/shared/AssetFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for getting assets on the platform.
class ENJINSDK_EXPORT GetAssets : public graphql::AbstractGraphqlRequest,
                                  public AssetFragmentArguments<GetAssets>,
                                  public PaginationArguments<GetAssets> {
public:
    /// \brief Default constructor.
    GetAssets();

    ~GetAssets() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetAssets& set_filter(const models::AssetFilter& filter);

    /// \brief Sets the request to sort the results by the specified options.
    /// \param sort The sort options.
    /// \return This request for chaining.
    GetAssets& set_sort(const models::AssetSort& sort);

    bool operator==(const GetAssets& rhs) const;

    bool operator!=(const GetAssets& rhs) const;

private:
    std::optional<models::AssetFilter> filter;
    std::optional<models::AssetSort> sort;
};

template ENJINSDK_EXPORT GetAssets&
AssetFragmentArguments<GetAssets>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_state_data();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_config_data();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_asset_blocks();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_creator();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_melt_details();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_metadata_uri();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_supply_details();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_transfer_settings();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_asset_variant_mode();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_asset_variants();

template ENJINSDK_EXPORT GetAssets& AssetFragmentArguments<GetAssets>::set_with_variant_metadata();

template ENJINSDK_EXPORT GetAssets&
PaginationArguments<GetAssets>::set_pagination(models::PaginationOptions pagination);

template ENJINSDK_EXPORT GetAssets& PaginationArguments<GetAssets>::set_pagination(int page, int limit);

}

#endif //ENJINCPPSDK_SHAREDGETASSETS_HPP
