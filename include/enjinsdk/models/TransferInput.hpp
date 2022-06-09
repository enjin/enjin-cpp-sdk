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

#ifndef ENJINCPPSDK_TRANSFERINPUT_HPP
#define ENJINCPPSDK_TRANSFERINPUT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a transfer input for transfer requests.
class ENJINSDK_EXPORT TransferInput : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    TransferInput() = default;

    ~TransferInput() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// Sets the source Ethereum address.
    /// \param address The source.
    /// \return This input for chaining.
    TransferInput& set_from(std::string address);

    /// Sets the destination Ethereum address.
    /// \param address The destination.
    /// \return This input for chaining.
    TransferInput& set_to(std::string address);

    /// Sets the asset ID to transfer or ENJ if unused.
    /// \param id The ID.
    /// \return This input for chaining.
    TransferInput& set_asset_id(std::string id);

    /// Sets the index for non-fungible assets.
    /// \param index The index.
    /// \return This input for chaining.
    TransferInput& set_asset_index(std::string index);

    /// Sets the amount of assets to transfer.
    /// \param value The amount.
    /// \return This input for chaining.
    TransferInput& set_value(std::string value);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const TransferInput& rhs) const;

    bool operator!=(const TransferInput& rhs) const;

private:
    std::optional<std::string> from_opt;
    std::optional<std::string> to_opt;
    std::optional<std::string> asset_id_opt;
    std::optional<std::string> asset_index_opt;
    std::optional<std::string> value_opt;
};

}

#endif //ENJINCPPSDK_TRANSFERINPUT_HPP
