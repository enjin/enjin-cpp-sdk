/* Copyright 2023 Enjin Pte. Ltd.
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

#ifndef ENJINSDK_PROJECTGETASSETSFROMPROJECTS_HPP
#define ENJINSDK_PROJECTGETASSETSFROMPROJECTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/AssetFilter.hpp"
#include "enjinsdk/models/AssetSortInput.hpp"
#include "enjinsdk/shared/AssetFragmentArguments.hpp"
#include "enjinsdk/shared/PaginationArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for getting assets from different projects on the platform.
class ENJINSDK_EXPORT GetAssetsFromProjects : public graphql::AbstractGraphqlRequest,
                                              public shared::AssetFragmentArguments<GetAssetsFromProjects>,
                                              public shared::PaginationArguments<GetAssetsFromProjects> {
public:
    /// \brief Default constructor.
    GetAssetsFromProjects();

    ~GetAssetsFromProjects() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the project UUIDs.
    /// \param projects The UUIDs.
    /// \return This request for chaining.
    GetAssetsFromProjects& set_projects(std::vector<std::string> projects);

    /// \brief Sets the filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetAssetsFromProjects& set_filter(models::AssetFilter filter);

    /// \brief Sets the request to sort the results by the specified options.
    /// \param sort The sort input.
    /// \return This request for chaining.
    GetAssetsFromProjects& set_sort(models::AssetSortInput sort);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const GetAssetsFromProjects& rhs) const;

    bool operator!=(const GetAssetsFromProjects& rhs) const;
    
private:
    std::optional<std::vector<std::string>> projects_opt;
    std::optional<models::AssetFilter> filter_opt;
    std::optional<models::AssetSortInput> sort_opt;
};

}

namespace enjin::sdk::shared {

// region AssetFragmentArguments

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_state_data();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_config_data();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_asset_blocks();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_creator();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_melt_details();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_metadata_uri();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_supply_details();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_transfer_settings();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_asset_variant_mode();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_asset_variants();

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
AssetFragmentArguments<project::GetAssetsFromProjects>::set_with_variant_metadata();

// endregion AssetFragmentArguments

// region PaginationArguments

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
PaginationArguments<project::GetAssetsFromProjects>::set_pagination(models::PaginationInput pagination);

template ENJINSDK_EXPORT project::GetAssetsFromProjects&
PaginationArguments<project::GetAssetsFromProjects>::set_pagination(int page, int limit);

// endregion PaginationArguments

}

#endif //ENJINSDK_PROJECTGETASSETSFROMPROJECTS_HPP
