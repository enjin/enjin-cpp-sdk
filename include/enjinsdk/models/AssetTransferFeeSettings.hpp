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

#ifndef ENJINCPPSDK_ASSETTRANSFERFEESETTINGS_HPP
#define ENJINCPPSDK_ASSETTRANSFERFEESETTINGS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/AssetTransferFeeType.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models transfer fee settings for an asset.
class ENJINSDK_EXPORT AssetTransferFeeSettings : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    AssetTransferFeeSettings();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    AssetTransferFeeSettings(const AssetTransferFeeSettings& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    AssetTransferFeeSettings(AssetTransferFeeSettings&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~AssetTransferFeeSettings() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the transfer fee type.
    /// \return The transfer type.
    [[nodiscard]] const std::optional<AssetTransferFeeType>& get_type() const;

    /// \brief Returns the asset ID or "0" if ENJ.
    /// \return The asset ID.
    [[nodiscard]] const std::optional<std::string>& get_asset_id() const;

    /// \brief Returns the fee value in Wei.
    /// \return The value.
    [[nodiscard]] const std::optional<std::string>& get_value() const;

    bool operator==(const AssetTransferFeeSettings& rhs) const;

    bool operator!=(const AssetTransferFeeSettings& rhs) const;

    AssetTransferFeeSettings& operator=(const AssetTransferFeeSettings& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_ASSETTRANSFERFEESETTINGS_HPP
