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
#include "enjinsdk/internal/AssetFragmentArgumentsImpl.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
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
        return impl.serialize();
    }

    /// \brief Sets the desired asset ID format.
    /// \param asset_id_format The format.
    /// \return This request for chaining.
    T& set_asset_id_format(models::AssetIdFormat asset_id_format) {
        impl.set_asset_id_format(asset_id_format);
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the state data with the asset.
    /// \return This request for chaining.
    T& set_with_state_data() {
        impl.set_with_state_data();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the configuration data with the asset.
    /// \return This request for chaining.
    T& set_with_config_data() {
        impl.set_with_config_data();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the block data with the asset when used with set_with_state_data().
    /// \return This request for chaining.
    T& set_with_asset_blocks() {
        impl.set_with_asset_blocks();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the creator with the asset when used with set_with_state_data().
    /// \return This request for chaining.
    T& set_with_creator() {
        impl.set_with_creator();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the melt details with the asset when used with set_with_config_data().
    /// \return This request for chaining.
    T& set_with_melt_details() {
        impl.set_with_melt_details();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata URI with the asset when used with set_with_config_data().
    /// \return This request for chaining.
    T& set_with_metadata_uri() {
        impl.set_with_metadata_uri();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the supply details with the asset when used with
    /// set_with_state_data().
    /// \return This request for chaining.
    T& set_with_supply_details() {
        impl.set_with_supply_details();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the transfer settings with the asset when used with
    /// set_with_config_data().
    /// \return This request for chaining.
    T& set_with_transfer_settings() {
        impl.set_with_transfer_settings();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variant mode with the asset.
    /// \return This request for chaining.
    T& set_with_asset_variant_mode() {
        impl.set_with_asset_variant_mode();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variants with the asset.
    /// \return This request for chaining.
    T& set_with_asset_variants() {
        impl.set_with_asset_variants();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata for the variants with the asset when used with
    /// set_with_asset_variants().
    /// \return This request for chaining.
    T& set_with_variant_metadata() {
        impl.set_with_variant_metadata();
        return static_cast<T&>(*this);
    }

    bool operator==(const AssetFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const AssetFragmentArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Sole constructor.
    AssetFragmentArguments() {
        static_assert(std::is_base_of<AssetFragmentArguments, T>::value,
                      "Class T does not inherit from AssetFragmentArguments.");
    }

private:
    AssetFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTS_HPP
