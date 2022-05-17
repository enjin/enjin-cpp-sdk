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

#ifndef ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/WalletFragmentArgumentsImpl.hpp"
#include "enjinsdk/shared/AssetFragmentArguments.hpp"
#include <string>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from wallets returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT WalletFragmentArguments : public AssetFragmentArguments<T> {
public:
    ~WalletFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    // WalletFragmentArguments functions

    /// Sets the request to include the assets created by the wallet.
    /// \return This request for chaining.
    virtual T& set_with_assets_created() {
        impl.set_with_assets_created();
        return dynamic_cast<T&>(*this);
    }

    // AssetFragmentArguments functions

    /// \brief Sets the desired asset ID format.
    /// \param asset_id_format The format.
    /// \return This request for chaining.
    virtual T& set_asset_id_format(models::AssetIdFormat asset_id_format) override {
        impl.set_asset_id_format(asset_id_format);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the state data with the asset.
    /// \return This request for chaining.
    virtual T& set_with_state_data() override {
        impl.set_with_state_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the configuration data with the asset.
    /// \return This request for chaining.
    virtual T& set_with_config_data() override {
        impl.set_with_config_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the block data with the asset when used with set_with_state_data().
    /// \return This request for chaining.
    virtual T& set_with_asset_blocks() override {
        impl.set_with_asset_blocks();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the creator with the asset when used with set_with_state_data().
    /// \return This request for chaining.
    virtual T& set_with_creator() override {
        impl.set_with_creator();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the melt details with the asset when used with set_with_config_data().
    /// \return This request for chaining.
    virtual T& set_with_melt_details() override {
        impl.set_with_melt_details();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata URI with the asset when used with set_with_config_data().
    /// \return This request for chaining.
    virtual T& set_with_metadata_uri() override {
        impl.set_with_metadata_uri();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the supply details with the asset when used with
    /// set_with_state_data().
    /// \return This request for chaining.
    virtual T& set_with_supply_details() override {
        impl.set_with_supply_details();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the transfer settings with the asset when used with
    /// set_with_config_data().
    /// \return This request for chaining.
    virtual T& set_with_transfer_settings() override {
        impl.set_with_transfer_settings();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variant mode with the asset.
    /// \return This request for chaining.
    virtual T& set_with_asset_variant_mode() override {
        impl.set_with_asset_variant_mode();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variants with the asset.
    /// \return This request for chaining.
    virtual T& set_with_asset_variants() override {
        impl.set_with_asset_variants();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata for the variants with the asset when used with
    /// set_with_asset_variants().
    /// \return This request for chaining.
    virtual T& set_with_variant_metadata() override {
        impl.set_with_variant_metadata();
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const WalletFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const WalletFragmentArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Default constructor.
    WalletFragmentArguments() = default;

private:
    WalletFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
