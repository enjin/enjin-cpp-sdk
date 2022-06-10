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
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models input for the transfer fee settings used in GraphQL requests.
class ENJINSDK_EXPORT AssetTransferFeeSettingsInput : public serialization::ISerializable {
public:
    /// \brief Constructs an instance of this class.
    AssetTransferFeeSettingsInput();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    AssetTransferFeeSettingsInput(const AssetTransferFeeSettingsInput& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    AssetTransferFeeSettingsInput(AssetTransferFeeSettingsInput&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~AssetTransferFeeSettingsInput() override;

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

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const AssetTransferFeeSettingsInput& rhs) const;

    bool operator!=(const AssetTransferFeeSettingsInput& rhs) const;

    AssetTransferFeeSettingsInput& operator=(const AssetTransferFeeSettingsInput& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINSDK_ASSETTRANSFERFEESETTINGSINPUT_HPP
