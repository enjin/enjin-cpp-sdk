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

#ifndef ENJINCPPSDK_WALLET_HPP
#define ENJINCPPSDK_WALLET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/Asset.hpp"
#include "enjinsdk/models/Balance.hpp"
#include "enjinsdk/models/Transaction.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

class Balance;

class Transaction;

/// \brief Models a wallet on the platform.
class ENJINSDK_EXPORT Wallet : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    Wallet();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    Wallet(const Wallet& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    Wallet(Wallet&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~Wallet() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the Ethereum address of this wallet.
    /// \return The address.
    [[nodiscard]] const std::optional<std::string>& get_eth_address() const;

    /// \brief Returns the ENJ allowance given for crypto-items.
    /// \return The allowance.
    [[nodiscard]] const std::optional<float>& get_enj_allowance() const;

    /// \brief Returns the ENJ balance for this wallet.
    /// \return The balance.
    [[nodiscard]] const std::optional<float>& get_enj_balance() const;

    /// \brief Returns the ETH balance for this wallet.
    /// \return The balance.
    [[nodiscard]] const std::optional<float>& get_eth_balance() const;

    /// \brief Returns the assets this wallet has created.
    /// \return The assets.
    [[nodiscard]] const std::optional<std::vector<Asset>>& get_assets_created() const;

    /// \brief Returns the balances of this wallet.
    /// \return The balances.
    [[nodiscard]] const std::optional<std::vector<Balance>>& get_balances() const;

    /// \brief Returns the transactions this wallet has signed.
    /// \return The transactions.
    [[nodiscard]] const std::optional<std::vector<Transaction>>& get_transactions() const;

    bool operator==(const Wallet& rhs) const;

    bool operator!=(const Wallet& rhs) const;

    Wallet& operator=(const Wallet& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> impl;
};

}

#endif //ENJINCPPSDK_WALLET_HPP
