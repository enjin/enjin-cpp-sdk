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

#ifndef ENJINCPPSDK_PROJECTSETAPPROVALFORALL_HPP
#define ENJINCPPSDK_PROJECTSETAPPROVALFORALL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for allowing an operator complete control of all assets owned by the caller.
class ENJINSDK_EXPORT SetApprovalForAll : public graphql::AbstractGraphqlRequest,
                                          public TransactionRequestArguments<SetApprovalForAll> {
public:
    /// \brief Default constructor.
    SetApprovalForAll();

    ~SetApprovalForAll() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the wallet address of the operator.
    /// \param operator_address The operator's address.
    /// \return This request for chaining.
    SetApprovalForAll& set_operator_address(std::string operator_address);

    /// \brief Sets the approval state.
    /// \param approved The approval.
    /// \return This request for chaining.
    SetApprovalForAll& set_approved(bool approved);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const SetApprovalForAll& rhs) const;

    bool operator!=(const SetApprovalForAll& rhs) const;

private:
    std::optional<std::string> operator_address_opt;
    std::optional<bool> approved_opt;
};

// region TransactionRequestArguments

template ENJINSDK_EXPORT SetApprovalForAll&
TransactionRequestArguments<SetApprovalForAll>::set_eth_address(std::string address);

// endregion TransactionRequestArguments

}

namespace enjin::sdk::shared {

// region TransactionFragmentArguments

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_meta();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_encoded_data();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_asset_data();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_signed_txs();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_error();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_nonce();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_state();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_receipt();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_log_event();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT project::SetApprovalForAll&
TransactionFragmentArguments<project::SetApprovalForAll>::set_with_transaction_wallet_address();

// endregion TransactionFragmentArguments

}

#endif //ENJINCPPSDK_PROJECTSETAPPROVALFORALL_HPP
