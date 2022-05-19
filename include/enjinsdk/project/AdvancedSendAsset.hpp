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

#ifndef ENJINCPPSDK_PROJECTADVANCEDSENDASSET_HPP
#define ENJINCPPSDK_PROJECTADVANCEDSENDASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Transfer.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for sending one or more assets in a single transaction.
class ENJINSDK_EXPORT AdvancedSendAsset : public graphql::AbstractGraphqlRequest,
                                          public ProjectTransactionRequestArguments<AdvancedSendAsset> {
public:
    /// \brief Default constructor.
    AdvancedSendAsset();

    ~AdvancedSendAsset() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the different transfers to perform.
    /// \param transfers The transfers.
    /// \return This request for chaining.
    AdvancedSendAsset& set_transfers(const std::vector<models::Transfer>& transfers);

    /// \brief Sets the data to forward with the transaction.
    /// \param data The data.
    /// \return This request for chaining.
    AdvancedSendAsset& set_data(const std::string& data);

    bool operator==(const AdvancedSendAsset& rhs) const;

    bool operator!=(const AdvancedSendAsset& rhs) const;

private:
    std::optional<std::vector<models::Transfer>> transfers;
    std::optional<std::string> data;
};

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_blockchain_data();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_meta();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_encoded_data();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_asset_data();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_signed_txs();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_error();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_nonce();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_state();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_receipt();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_receipt_logs();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_log_event();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT AdvancedSendAsset&
ProjectTransactionRequestArguments<AdvancedSendAsset>::set_eth_address(const std::string& address);

}

#endif //ENJINCPPSDK_PROJECTADVANCEDSENDASSET_HPP
