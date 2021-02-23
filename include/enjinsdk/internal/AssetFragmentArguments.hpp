#ifndef ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP

#include "enjinsdk/models/AssetIdFormat.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Asset fragment.
class AssetFragmentArguments : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    AssetFragmentArguments() = default; // TODO: Consider making this constructor private and friend to its implementing template class.

    ~AssetFragmentArguments() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to the passed value.
    /// \param asset_id_format The ID format.
    void set_asset_id_format(models::AssetIdFormat asset_id_format);

    /// \brief Sets the value for the associated field to true.
    void set_with_state_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_config_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_asset_blocks();

    /// \brief Sets the value for the associated field to true.
    void set_with_creator();

    /// \brief Sets the value for the associated field to true.
    void set_with_melt_details();

    /// \brief Sets the value for the associated field to true.
    void set_with_metadata_uri();

    /// \brief Sets the value for the associated field to true.
    void set_with_supply_details();

    /// \brief Sets the value for the associated field to true.
    void set_with_transfer_settings();

    /// \brief Sets the value for the associated field to true.
    void set_with_asset_variant_mode();

    /// \brief Sets the value for the associated field to true.
    void set_with_asset_variants();

    /// \brief Sets the value for the associated field to true.
    void set_with_variant_metadata();

    bool operator==(const AssetFragmentArguments& rhs) const;

    bool operator!=(const AssetFragmentArguments& rhs) const;

private:
    std::optional<models::AssetIdFormat> asset_id_format;
    std::optional<bool> with_state_data;
    std::optional<bool> with_config_data;
    std::optional<bool> with_asset_blocks;
    std::optional<bool> with_creator;
    std::optional<bool> with_melt_details;
    std::optional<bool> with_metadata_uri;
    std::optional<bool> with_supply_details;
    std::optional<bool> with_transfer_settings;
    std::optional<bool> with_asset_variant_mode;
    std::optional<bool> with_asset_variants;
    std::optional<bool> with_variant_metadata;
};

}

#endif //ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP
