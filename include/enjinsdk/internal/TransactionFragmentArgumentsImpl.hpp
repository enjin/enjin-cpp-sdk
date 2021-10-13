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

#ifndef ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Transaction fragment.
class ENJINSDK_EXPORT TransactionFragmentArgumentsImpl : public serialization::ISerializable {
public:
    /// \brief Default constructor to be used internally.
    TransactionFragmentArgumentsImpl() = default;

    ~TransactionFragmentArgumentsImpl() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the value for the associated field to the passed value.
    /// \param asset_id_format The ID format.
    void set_asset_id_format(models::AssetIdFormat asset_id_format);

    /// \brief Sets the value for the associated field to true.
    void set_with_blockchain_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_meta();

    /// \brief Sets the value for the associated field to true.
    void set_with_encoded_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_asset_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_signed_txs();

    /// \brief Sets the value for the associated field to true.
    void set_with_error();

    /// \brief Sets the value for the associated field to true.
    void set_with_nonce();

    /// \brief Sets the value for the associated field to true.
    void set_with_state();

    /// \brief Sets the value for the associated field to true.
    void set_with_receipt();

    /// \brief Sets the value for the associated field to true.
    void set_with_receipt_logs();

    /// \brief Sets the value for the associated field to true.
    void set_with_log_event();

    /// \brief Sets the value for the associated field to true.
    void set_with_transaction_project_uuid();

    bool operator==(const TransactionFragmentArgumentsImpl& rhs) const;

    bool operator!=(const TransactionFragmentArgumentsImpl& rhs) const;

private:
    std::optional<models::AssetIdFormat> asset_id_format;
    std::optional<bool> with_blockchain_data;
    std::optional<bool> with_meta;
    std::optional<bool> with_encoded_data;
    std::optional<bool> with_asset_data;
    std::optional<bool> with_signed_txs;
    std::optional<bool> with_error;
    std::optional<bool> with_nonce;
    std::optional<bool> with_state;
    std::optional<bool> with_receipt;
    std::optional<bool> with_receipt_logs;
    std::optional<bool> with_log_event;
    std::optional<bool> with_transaction_project_uuid;
};

}

#endif //ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTSIMPL_HPP
