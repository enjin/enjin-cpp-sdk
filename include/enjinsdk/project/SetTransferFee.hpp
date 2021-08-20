/* Copyright 2021 Enjin Pte Ltd.
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
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting the transfer fee of a asset.
class ENJINSDK_EXPORT SetTransferFee : public graphql::AbstractGraphqlRequest,
                                       public ProjectTransactionRequestArguments<SetTransferFee> {
public:
    /// \brief Default constructor.
    SetTransferFee();

    ~SetTransferFee() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SetTransferFee& set_asset_id(const std::string& asset_id);

    /// \brief Sets the new transfer fee value in Wei.
    /// \param transfer_fee The new transfer fee.
    /// \return This request for chaining.
    SetTransferFee& set_transfer_fee(const std::string& transfer_fee);

    bool operator==(const SetTransferFee& rhs) const;

    bool operator!=(const SetTransferFee& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> transfer_fee;
};

template ENJINSDK_EXPORT SetTransferFee&
ProjectTransactionRequestArguments<SetTransferFee>::set_eth_address(const std::string& address);

}

namespace enjin::sdk::shared {

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

}

#endif //ENJINCPPSDK_PROJECTSETTRANSFERFEE_HPP
