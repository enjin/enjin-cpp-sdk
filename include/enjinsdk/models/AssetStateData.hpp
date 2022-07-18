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

#ifndef ENJINCPPSDK_ASSETSTATEDATA_HPP
#define ENJINCPPSDK_ASSETSTATEDATA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/AssetSupplyModel.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the state data of a asset.
class ENJINSDK_EXPORT AssetStateData : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    AssetStateData();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    AssetStateData(const AssetStateData& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    AssetStateData(AssetStateData&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~AssetStateData() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the fungible state of the asset this state belongs to.
    /// \return Whether this asset is fungible.
    [[nodiscard]] const std::optional<bool>& get_non_fungible() const;

    /// \brief Returns the block number of the last update.
    /// \return The block number.
    [[nodiscard]] const std::optional<int>& get_block_height() const;

    /// \brief Returns the wallet address of the creator of the asset this state belongs to.
    /// \return The creator's wallet address.
    [[nodiscard]] const std::optional<std::string>& get_creator() const;

    /// \brief Returns the first block the asset appeared on.
    /// \return The block number.
    [[nodiscard]] const std::optional<int>& get_first_block() const;

    /// \brief Returns the reserve of the asset this state belongs to.
    /// \return The reserve amount.
    [[nodiscard]] const std::optional<std::string>& get_reserve() const;

    /// \brief Returns the supply model of the asset this state belongs to.
    /// \return The supply model.
    [[nodiscard]] const std::optional<AssetSupplyModel>& get_supply_model() const;

    /// \brief Returns the amount of the asset in circulation.
    /// \return The amount in circulation.
    [[nodiscard]] const std::optional<std::string>& get_circulating_supply() const;

    /// \brief Returns the amount of the asset available for minting.
    /// \return The amount available.
    [[nodiscard]] const std::optional<std::string>& get_mintable_supply() const;

    /// \brief Returns the total supply of the asset this state belongs to.
    /// \return The total supply.
    [[nodiscard]] const std::optional<std::string>& get_total_supply() const;

    bool operator==(const AssetStateData& rhs) const;

    bool operator!=(const AssetStateData& rhs) const;

    AssetStateData& operator=(const AssetStateData& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_ASSETSTATEDATA_HPP
