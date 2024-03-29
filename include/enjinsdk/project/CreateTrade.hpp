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
#include "enjinsdk/models/TradeInput.hpp"
#include "enjinsdk/project/TransactionRequestArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for creating a trade between two wallets.
class ENJINSDK_EXPORT CreateTrade : public graphql::AbstractGraphqlRequest,
                                    public TransactionRequestArguments<CreateTrade> {
public:
    /// \brief Default constructor.
    CreateTrade();

    ~CreateTrade() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the assets the sender is asking for.
    /// \param assets The assets.
    /// \return This request for chaining.
    CreateTrade& set_asking_assets(std::vector<models::TradeInput> assets);

    /// \brief Sets the assets to be offered bu the sender.
    /// \param assets The assets.
    /// \return This request for chaining.
    CreateTrade& set_offering_assets(std::vector<models::TradeInput> assets);

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    CreateTrade& set_recipient_address(std::string recipient_address);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const CreateTrade& rhs) const;

    bool operator!=(const CreateTrade& rhs) const;

private:
    std::optional<std::vector<models::TradeInput>> asking_assets_opt;
    std::optional<std::vector<models::TradeInput>> offering_assets_opt;
    std::optional<std::string> recipient_address_opt;
};

// region TransactionRequestArguments

template ENJINSDK_EXPORT CreateTrade&
TransactionRequestArguments<CreateTrade>::set_eth_address(std::string address);

// endregion TransactionRequestArguments

}

namespace enjin::sdk::shared {

// region TransactionFragmentArguments

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

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

template ENJINSDK_EXPORT project::CreateTrade&
TransactionFragmentArguments<project::CreateTrade>::set_with_transaction_wallet_address();

// endregion TransactionFragmentArguments

}

#endif //ENJINCPPSDK_PROJECTCREATETRADE_HPP
