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

#ifndef ENJINCPPSDK_PROJECTCREATETRADE_HPP
#define ENJINCPPSDK_PROJECTCREATETRADE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Trade.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for creating a trade between two wallets.
class ENJINSDK_EXPORT CreateTrade : public graphql::AbstractGraphqlRequest,
                                    public ProjectTransactionRequestArguments<CreateTrade> {
public:
    /// \brief Default constructor.
    CreateTrade();

    ~CreateTrade() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the assets the sender is asking for.
    /// \param assets The assets.
    /// \return This request for chaining.
    CreateTrade& set_asking_assets(std::vector<models::Trade> assets);

    /// \brief Sets the assets to be offered bu the sender.
    /// \param assets The assets.
    /// \return This request for chaining.
    CreateTrade& set_offering_assets(std::vector<models::Trade> assets);

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    CreateTrade& set_recipient_address(const std::string& recipient_address);

    bool operator==(const CreateTrade& rhs) const;

    bool operator!=(const CreateTrade& rhs) const;

private:
    std::optional<std::vector<models::Trade>> asking_assets;
    std::optional<std::vector<models::Trade>> offering_assets;
    std::optional<std::string> recipient_address;
};

template ENJINSDK_EXPORT CreateTrade&
ProjectTransactionRequestArguments<CreateTrade>::set_eth_address(const std::string& address);

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_meta();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_encoded_data();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_asset_data();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_signed_txs();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_error();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_nonce();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_state();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_receipt();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_log_event();

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_transaction_project_uuid();

}

#endif //ENJINCPPSDK_PROJECTCREATETRADE_HPP
