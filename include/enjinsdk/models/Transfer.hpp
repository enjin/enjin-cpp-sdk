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

#ifndef ENJINCPPSDK_TRANSFER_HPP
#define ENJINCPPSDK_TRANSFER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a transfer input for transfer requests.
class ENJINSDK_EXPORT Transfer : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    Transfer() = default;

    ~Transfer() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// Sets the source Ethereum address.
    /// \param address The source.
    /// \return This input for chaining.
    Transfer& set_from(std::string address);

    /// Sets the destination Ethereum address.
    /// \param address The destination.
    /// \return This input for chaining.
    Transfer& set_to(std::string address);

    /// Sets the asset ID to transfer or ENJ if unused.
    /// \param id The ID.
    /// \return This input for chaining.
    Transfer& set_asset_id(std::string id);

    /// Sets the index for non-fungible assets.
    /// \param index The index.
    /// \return This input for chaining.
    Transfer& set_asset_index(std::string index);

    /// Sets the amount of assets to transfer.
    /// \param value The amount.
    /// \return This input for chaining.
    Transfer& set_value(std::string value);

    bool operator==(const Transfer& rhs) const;

    bool operator!=(const Transfer& rhs) const;

private:
    std::optional<std::string> from;
    std::optional<std::string> to;
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> value;

    constexpr static char FROM_KEY[] = "from";
    constexpr static char TO_KEY[] = "to";
    constexpr static char ASSET_ID_KEY[] = "assetId";
    constexpr static char ASSET_INDEX_KEY[] = "assetIndex";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINCPPSDK_TRANSFER_HPP
