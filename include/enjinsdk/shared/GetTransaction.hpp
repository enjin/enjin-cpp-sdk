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

#ifndef ENJINCPPSDK_SHAREDGETTRANSACTION_HPP
#define ENJINCPPSDK_SHAREDGETTRANSACTION_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for getting a transaction on the platform.
class ENJINSDK_EXPORT GetTransaction : public graphql::AbstractGraphqlRequest,
                                       public TransactionFragmentArguments<GetTransaction> {
public:
    /// \brief Default constructor.
    GetTransaction();

    ~GetTransaction() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the transaction ID.
    /// \param id The ID.
    /// \return This request for chaining.
    GetTransaction& set_id(int id);

    /// \brief Sets the transaction hash ID.
    /// \param id The hash ID.
    /// \return This request for chaining.
    GetTransaction& set_transaction_id(std::string id);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const GetTransaction& rhs) const;

    bool operator!=(const GetTransaction& rhs) const;

private:
    std::optional<int> id_opt;
    std::optional<std::string> transaction_id_opt;
};

// region TransactionFragmentArguments

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_transaction_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_blockchain_data();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_meta();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_encoded_data();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_asset_data();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_signed_txs();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_error();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_nonce();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_state();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_receipt();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_receipt_logs();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_log_event();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT GetTransaction&
TransactionFragmentArguments<GetTransaction>::set_with_transaction_wallet_address();

// endregion TransactionFragmentArguments

}

#endif //ENJINCPPSDK_SHAREDGETTRANSACTION_HPP
