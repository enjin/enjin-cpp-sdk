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

#ifndef ENJINCPPSDK_PLAYERAPPROVEENJ_HPP
#define ENJINCPPSDK_PLAYERAPPROVEENJ_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::player {

/// \brief Request for approving the crypto items contract to spend ENJ.
class ENJINSDK_EXPORT ApproveEnj : public graphql::AbstractGraphqlRequest,
                                   public shared::TransactionFragmentArguments<ApproveEnj> {
public:
    /// \brief Default constructor.
    ApproveEnj();

    ~ApproveEnj() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the amount of ENJ to approve.
    /// \param value The value.
    /// \return This request for chaining.
    /// \remarks The value is in Wei as 10^18 (e.g. 1 ENJ = 1000000000000000000).
    ApproveEnj& set_value(std::string value);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const ApproveEnj& rhs) const;

    bool operator!=(const ApproveEnj& rhs) const;

private:
    std::optional<std::string> value_opt;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_blockchain_data();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_meta();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_encoded_data();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_asset_data();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_signed_txs();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_error();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_nonce();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_state();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_receipt();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_receipt_logs();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_log_event();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT player::ApproveEnj&
TransactionFragmentArguments<player::ApproveEnj>::set_with_transaction_wallet_address();

}

#endif //ENJINCPPSDK_PROJECTAPPROVEENJ_HPP
