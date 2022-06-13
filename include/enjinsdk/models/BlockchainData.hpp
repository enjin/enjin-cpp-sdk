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

#ifndef ENJINCPPSDK_BLOCKCHAINDATA_HPP
#define ENJINCPPSDK_BLOCKCHAINDATA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/TransactionReceipt.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the blockchain data of a request.
class ENJINSDK_EXPORT BlockchainData : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    BlockchainData();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    BlockchainData(const BlockchainData& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    BlockchainData(BlockchainData&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~BlockchainData() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the encoded data of the request this data container belongs to.
    /// \return The encoded data.
    [[nodiscard]] const std::optional<std::string>& get_encoded_data() const;

    /// \brief Returns the signed string of the request this data container belongs to.
    /// \return The signed string.
    [[nodiscard]] const std::optional<std::string>& get_signed_transaction() const;

    /// \brief Returns the signed backup string of the request this data container belongs to.
    /// \return The signed backup string.
    [[nodiscard]] const std::optional<std::string>& get_signed_backup_transaction() const;

    /// \brief Returns the signed cancel string of the request this data container belongs to.
    /// \return The signed cancel string.
    [[nodiscard]] const std::optional<std::string>& get_signed_cancel_transaction() const;

    /// \brief Returns the receipt of the request this data container belongs to.
    /// \return The receipt.
    [[nodiscard]] const std::optional<TransactionReceipt>& get_receipt() const;

    /// \brief Returns the error message of the request this data container belongs to.
    /// \return The error message.
    [[nodiscard]] const std::optional<std::string>& get_error() const;

    /// \brief Returns the nonce of the request this data container belongs to.
    /// \return The nonce.
    [[nodiscard]] const std::optional<std::string>& get_nonce() const;

    bool operator==(const BlockchainData& rhs) const;

    bool operator!=(const BlockchainData& rhs) const;

    BlockchainData& operator=(const BlockchainData& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_BLOCKCHAINDATA_HPP
