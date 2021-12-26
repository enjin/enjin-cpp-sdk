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

#ifndef ENJINSDK_ASSETTRANSFERFEESETTINGSINPUT_HPP
#define ENJINSDK_ASSETTRANSFERFEESETTINGSINPUT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/AssetTransferFeeSettings.hpp"
#include "enjinsdk/models/AssetTransferFeeType.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models input for the transfer fee settings used in GraphQL requests.
class ENJINSDK_EXPORT AssetTransferFeeSettingsInput : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    AssetTransferFeeSettingsInput() = default;

    ~AssetTransferFeeSettingsInput() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the transfer type for this input.
    /// \param type The type.
    /// \return This input for chaining.
    AssetTransferFeeSettingsInput& set_type(AssetTransferFeeType type);

    /// \brief Sets the asset ID for this input.
    /// \param asset_id The ID.
    /// \return This input for chaining.
    AssetTransferFeeSettingsInput& set_asset_id(std::string asset_id);

    /// \brief Sets the value in Wei for this input.
    /// \param value The value.
    /// \return This input for chaining.
    AssetTransferFeeSettingsInput& set_value(std::string value);

    bool operator==(const AssetTransferFeeSettingsInput& rhs) const;

    bool operator!=(const AssetTransferFeeSettingsInput& rhs) const;

private:
    std::optional<AssetTransferFeeType> type;
    std::optional<std::string> asset_id;
    std::optional<std::string> value;

    constexpr static char TYPE_KEY[] = "type";
    constexpr static char ASSET_ID_KEY[] = "assetId";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINSDK_ASSETTRANSFERFEESETTINGSINPUT_HPP