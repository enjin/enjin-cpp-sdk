#ifndef ENJINCPPSDK_SHAREDGETASSET_HPP
#define ENJINCPPSDK_SHAREDGETASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Asset.hpp"
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
    GetAsset& set_id(const std::string& id);

    bool operator==(const GetAsset& rhs) const;

    bool operator!=(const GetAsset& rhs) const;

private:
    std::optional<std::string> id;
};

template ENJINSDK_EXPORT GetAsset&
AssetFragmentArguments<GetAsset>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_state_data();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_config_data();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_asset_blocks();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_creator();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_melt_details();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_metadata_uri();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_supply_details();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_transfer_settings();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_asset_variant_mode();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_asset_variants();

template ENJINSDK_EXPORT GetAsset& AssetFragmentArguments<GetAsset>::set_with_variant_metadata();

}

#endif //ENJINCPPSDK_SHAREDGETASSET_HPP
