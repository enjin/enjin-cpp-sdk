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

#ifndef ENJINCPPSDK_CONTRACTS_HPP
#define ENJINCPPSDK_CONTRACTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/SupplyModels.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a smart contract used by the platform.
class ENJINSDK_EXPORT Contracts : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Contracts() = default;

    ~Contracts() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ENJ contract address.
    /// \return The contract address.
    [[nodiscard]] const std::optional<std::string>& get_enj() const;

    /// \brief Returns the crypto items contract address.
    /// \return The contract address.
    [[nodiscard]] const std::optional<std::string>& get_crypto_items() const;

    /// \brief Returns the platform registry contract address.
    /// \return The contract address.
    [[nodiscard]] const std::optional<std::string>& get_platform_registry() const;

    /// \brief Returns the supply models used by the platform.
    /// \return The supply models.
    [[nodiscard]] const std::optional<SupplyModels>& get_supply_models() const;

    bool operator==(const Contracts& rhs) const;

    bool operator!=(const Contracts& rhs) const;

private:
    std::optional<std::string> enj;
    std::optional<std::string> crypto_items;
    std::optional<std::string> platform_registry;
    std::optional<SupplyModels> supply_models;
};

}

#endif //ENJINCPPSDK_CONTRACTS_HPP
