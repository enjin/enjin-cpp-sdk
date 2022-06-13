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

#ifndef ENJINCPPSDK_TRANSACTION_HPP
#define ENJINCPPSDK_TRANSACTION_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/Asset.hpp"
#include "enjinsdk/models/BlockchainData.hpp"
#include "enjinsdk/models/Project.hpp"
#include "enjinsdk/models/TransactionState.hpp"
#include "enjinsdk/models/TransactionType.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

class Wallet;

/// \brief Models a transaction on the platform.
class ENJINSDK_EXPORT Transaction : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    Transaction();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    Transaction(const Transaction& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    Transaction(Transaction&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~Transaction() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this transaction.
    /// \return The ID.
    [[nodiscard]] const std::optional<int>& get_id() const;

    /// \brief Returns the hash ID of this transaction.
    /// \return The hash ID.
    [[nodiscard]] const std::optional<std::string>& get_transaction_id() const;

    /// \brief Returns the title of this transaction.
    /// \return The title.
    [[nodiscard]] const std::optional<std::string>& get_title() const;

    /// \brief Returns the contract address of this transaction.
    /// \return The address.
    [[nodiscard]] const std::optional<std::string>& get_contract() const;

    /// \brief Returns the type of this transaction.
    /// \return The transaction type.
    [[nodiscard]] const std::optional<TransactionType>& get_type() const;

    /// \brief Returns the value of this transaction.
    /// \return The value.
    [[nodiscard]] const std::optional<std::string>& get_value() const;

    /// \brief Returns the retry state of this transaction.
    /// \return The retry state.
    [[nodiscard]] const std::optional<std::string>& get_retry_state() const;

    /// \brief Returns the state of this transaction.
    /// \return The transaction state.
    [[nodiscard]] const std::optional<TransactionState>& get_state() const;

    /// \brief Returns if this transaction has been accepted or not.
    /// \return Whether this transaction has been accepted or not.
    [[nodiscard]] const std::optional<bool>& get_accepted() const;

    /// \brief Returns if the wallet of the transaction is a project wallet.
    /// \return Whether the wallet is a project wallet.
    [[nodiscard]] const std::optional<bool>& get_project_wallet() const;

    /// \brief Returns the blockchain data of this transaction.
    /// \return The blockchain data.
    [[nodiscard]] const std::optional<BlockchainData>& get_blockchain_data() const;

    /// \brief Returns the project of this transaction.
    /// \return The project.
    [[nodiscard]] const std::optional<Project>& get_project() const;

    /// \brief Returns the asset for this transaction.
    /// \return The asset.
    [[nodiscard]] const std::optional<Asset>& get_asset() const;

    /// Returns the wallet for this transaction.
    /// \return The wallet.
    [[nodiscard]] const std::optional<Wallet>& get_wallet() const;

    /// \brief Returns the datetime when this transaction was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this transaction was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

    bool operator==(const Transaction& rhs) const;

    bool operator!=(const Transaction& rhs) const;

    Transaction& operator=(const Transaction& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_TRANSACTION_HPP
