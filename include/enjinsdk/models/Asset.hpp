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

#ifndef ENJINCPPSDK_ASSET_HPP
#define ENJINCPPSDK_ASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/AssetConfigData.hpp"
#include "enjinsdk/models/AssetStateData.hpp"
#include "enjinsdk/models/AssetVariant.hpp"
#include "enjinsdk/models/AssetVariantMode.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a asset on the platform.
class ENJINSDK_EXPORT Asset : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    Asset();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    Asset(const Asset& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    Asset(Asset&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~Asset() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this asset.
    /// \return The ID.
    [[nodiscard]] const std::optional<std::string>& get_id() const;

    /// \brief Returns the name of this asset.
    /// \return The name.
    [[nodiscard]] const std::optional<std::string>& get_name() const;

    /// \brief Returns the state data of this asset.
    /// \return The state data.
    [[nodiscard]] const std::optional<AssetStateData>& get_state_data() const;

    /// \brief Returns the configuration data of this asset.
    /// \return The configuration data.
    [[nodiscard]] const std::optional<AssetConfigData>& get_config_data() const;

    /// \brief Returns the asset variant mode of this asset.
    /// \return The variant mode.
    [[nodiscard]] const std::optional<AssetVariantMode>& get_variant_mode() const;

    /// \brief Returns the asset variants of this asset.
    /// \return The variants.
    [[nodiscard]] const std::optional<std::vector<AssetVariant>>& get_variants() const;

    /// \brief Returns the datetime when this asset was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this asset was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

    bool operator==(const Asset& rhs) const;

    bool operator!=(const Asset& rhs) const;

    Asset& operator=(const Asset& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_ASSET_HPP
