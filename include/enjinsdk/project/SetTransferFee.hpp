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

#ifndef ENJINCPPSDK_PROJECTSETTRANSFERFEE_HPP
#define ENJINCPPSDK_PROJECTSETTRANSFERFEE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting the transfer fee of a asset.
class ENJINSDK_EXPORT SetTransferFee : public graphql::AbstractGraphqlRequest,
                                       public TransactionRequestArguments<SetTransferFee> {
public:
    /// \brief Default constructor.
    SetTransferFee();

    ~SetTransferFee() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SetTransferFee& set_asset_id(std::string asset_id);

    /// \brief Sets the new transfer fee value in Wei.
    /// \param transfer_fee The new transfer fee.
    /// \return This request for chaining.
    SetTransferFee& set_transfer_fee(std::string transfer_fee);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const SetTransferFee& rhs) const;

    bool operator!=(const SetTransferFee& rhs) const;

private:
    std::optional<std::string> asset_id_opt;
    std::optional<std::string> transfer_fee_opt;
};

// region TransactionRequestArguments

template ENJINSDK_EXPORT SetTransferFee&
TransactionRequestArguments<SetTransferFee>::set_eth_address(std::string address);

// endregion TransactionRequestArguments

}

namespace enjin::sdk::shared {

// region TransactionFragmentArguments

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_meta();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_encoded_data();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_asset_data();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_signed_txs();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_error();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_nonce();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_state();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_receipt();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_log_event();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT project::SetTransferFee&
TransactionFragmentArguments<project::SetTransferFee>::set_with_transaction_wallet_address();

// endregion TransactionFragmentArguments

}

#endif //ENJINCPPSDK_PROJECTSETTRANSFERFEE_HPP
