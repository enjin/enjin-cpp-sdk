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

    std::string serialize() override;

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
