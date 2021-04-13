#ifndef ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/internal/AssetFragmentArgumentsImpl.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from assets returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT AssetFragmentArguments : public serialization::ISerializable {
public:
    ~AssetFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    /// \brief Sets the desired asset ID format.
    /// \param asset_id_format The format.
    /// \return This request for chaining.
    T& set_asset_id_format(models::AssetIdFormat asset_id_format) {
        impl.set_asset_id_format(asset_id_format);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the state data with the asset.
    /// \return This request for chaining.
    T& set_with_state_data() {
        impl.set_with_state_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the configuration data with the asset.
    /// \return This request for chaining.
    T& set_with_config_data() {
        impl.set_with_config_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the block data with the asset when used with set_with_state_data().
    /// \return This request for chaining.
    T& set_with_asset_blocks() {
        impl.set_with_asset_blocks();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the creator with the asset when used with set_with_state_data().
    /// \return This request for chaining.
    T& set_with_creator() {
        impl.set_with_creator();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the melt details with the asset when used with set_with_config_data().
    /// \return This request for chaining.
    T& set_with_melt_details() {
        impl.set_with_melt_details();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata URI with the asset when used with set_with_config_data().
    /// \return This request for chaining.
    T& set_with_metadata_uri() {
        impl.set_with_metadata_uri();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the supply details with the asset when used with
    /// set_with_state_data().
    /// \return This request for chaining.
    T& set_with_supply_details() {
        impl.set_with_supply_details();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the transfer settings with the asset when used with
    /// set_with_config_data().
    /// \return This request for chaining.
    T& set_with_transfer_settings() {
        impl.set_with_transfer_settings();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variant mode with the asset.
    /// \return This request for chaining.
    T& set_with_asset_variant_mode() {
        impl.set_with_asset_variant_mode();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variants with the asset.
    /// \return This request for chaining.
    T& set_with_asset_variants() {
        impl.set_with_asset_variants();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata for the variants with the asset when used with
    /// set_with_asset_variants().
    /// \return This request for chaining.
    T& set_with_variant_metadata() {
        impl.set_with_variant_metadata();
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const AssetFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const AssetFragmentArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Default constructor.
    AssetFragmentArguments() = default;

private:
    AssetFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP
