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

#ifndef ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP
#define ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting an asset's max transfer fee to a lower value.
class ENJINSDK_EXPORT DecreaseMaxTransferFee : public graphql::AbstractGraphqlRequest,
                                               public ProjectTransactionRequestArguments<DecreaseMaxTransferFee> {
public:
    /// \brief Default constructor.
    DecreaseMaxTransferFee();

    ~DecreaseMaxTransferFee() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_asset_id(std::string asset_id);

    /// \brief Sets the new max transfer fee in Wei.
    /// \param max_transfer_fee The new fee.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_max_transfer_fee(int max_transfer_fee);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const DecreaseMaxTransferFee& rhs) const;

    bool operator!=(const DecreaseMaxTransferFee& rhs) const;

private:
    std::optional<std::string> asset_id_opt;
    std::optional<int> max_transfer_fee_opt;
};

// region ProjectTransactionRequestArguments

template ENJINSDK_EXPORT DecreaseMaxTransferFee&
ProjectTransactionRequestArguments<DecreaseMaxTransferFee>::set_eth_address(std::string address);

// endregion ProjectTransactionRequestArguments

}

namespace enjin::sdk::shared {

// region TransactionFragmentArguments

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_meta();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_encoded_data();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_asset_data();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_signed_txs();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_error();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_nonce();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_state();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_receipt();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_log_event();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_transaction_wallet_address();

// endregion TransactionFragmentArguments

}

#endif //ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP
