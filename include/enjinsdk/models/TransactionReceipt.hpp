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

#ifndef ENJINCPPSDK_TRANSACTIONRECEIPT_HPP
#define ENJINCPPSDK_TRANSACTIONRECEIPT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/TransactionLog.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a receipt for a blockchain transaction.
class ENJINSDK_EXPORT TransactionReceipt : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    TransactionReceipt();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    TransactionReceipt(const TransactionReceipt& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    TransactionReceipt(TransactionReceipt&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~TransactionReceipt() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the hash of the block for the transaction this receipt belongs to.
    /// \return The block hash.
    [[nodiscard]] const std::optional<std::string>& get_block_hash() const;

    /// \brief Returns the block number where the transaction this receipt belongs to is.
    /// \return The block number.
    [[nodiscard]] const std::optional<int>& get_block_number() const;

    /// \brief Returns the total amount of gas used when the transaction was executed in the block.
    /// \return The total gas used.
    [[nodiscard]] const std::optional<int>& get_cumulative_gas_used() const;

    /// \brief Returns the gas used by the specific transaction alone.
    /// \return The gas used.
    [[nodiscard]] const std::optional<int>& get_gas_used() const;

    /// \brief Returns the sender address for the transaction this receipt belongs to.
    /// \return The sender address.
    [[nodiscard]] const std::optional<std::string>& get_from() const;

    /// \brief Returns the receiver address for the transaction this receipt belongs to.
    /// \return The receiver address.
    /// \remarks If the transaction was for contract creation, then the optional will not have a value.
    [[nodiscard]] const std::optional<std::string>& get_to() const;

    /// \brief Returns the hash of the transaction this receipt belongs to.
    /// \return The hash.
    [[nodiscard]] const std::optional<std::string>& get_transaction_hash() const;

    /// \brief Returns the index position in the block for the transaction this receipt belongs to.
    /// \return The index position.
    [[nodiscard]] const std::optional<int>& get_transaction_index() const;

    /// \brief Returns the status for the transaction this receipt belongs to.
    /// \return The status.
    [[nodiscard]] const std::optional<bool>& get_status() const;

    /// \brief Returns the transaction logs generated for the transaction this receipt belongs to.
    /// \return The transaction logs.
    [[nodiscard]] const std::optional<std::vector<TransactionLog>>& get_logs() const;

    bool operator==(const TransactionReceipt& rhs) const;

    bool operator!=(const TransactionReceipt& rhs) const;

    TransactionReceipt& operator=(const TransactionReceipt& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_TRANSACTIONRECEIPT_HPP
