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

#ifndef ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Asset fragment.
class ENJINSDK_EXPORT AssetFragmentArgumentsImpl : public serialization::ISerializable {
public:
    /// \brief Default constructor to be used internally.
    AssetFragmentArgumentsImpl() = default;

    ~AssetFragmentArgumentsImpl() override = default;

    [[nodiscard]] std::string serialize() const override;

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

    bool operator==(const AssetFragmentArgumentsImpl& rhs) const;

    bool operator!=(const AssetFragmentArgumentsImpl& rhs) const;

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

#endif //ENJINCPPSDK_SHAREDASSETFRAGMENTARGUMENTSIMPL_HPP
