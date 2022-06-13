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

#ifndef ENJINCPPSDK_PROJECTGETWALLET_HPP
#define ENJINCPPSDK_PROJECTGETWALLET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/WalletFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for getting a wallet from the platform.
class ENJINSDK_EXPORT GetWallet : public graphql::AbstractGraphqlRequest,
                                  public shared::WalletFragmentArguments<GetWallet> {
public:
    /// \brief Default constructor.
    GetWallet();

    ~GetWallet() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the user ID owning the wallet to get.
    /// \param user_id The user ID.
    /// \return This request for chaining.
    GetWallet& set_user_id(std::string user_id);

    /// \brief Sets the Ethereum address of the wallet to get.
    /// \param eth_address The address.
    /// \return This request for chaining.
    GetWallet& set_eth_address(std::string eth_address);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const GetWallet& rhs) const;

    bool operator!=(const GetWallet& rhs) const;

private:
    std::optional<std::string> user_id_opt;
    std::optional<std::string> eth_address_opt;
};

}

namespace enjin::sdk::shared {

// region AssetFragmentArguments

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_state_data();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_config_data();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_asset_blocks();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_creator();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_melt_details();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_metadata_uri();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_supply_details();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_transfer_settings();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_asset_variant_mode();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_asset_variants();

template ENJINSDK_EXPORT project::GetWallet&
AssetFragmentArguments<project::GetWallet>::set_with_variant_metadata();

// endregion AssetFragmentArguments

// region BalanceFragmentArguments

template ENJINSDK_EXPORT project::GetWallet&
BalanceFragmentArguments<project::GetWallet>::set_bal_id_format(models::AssetIdFormat bal_id_format);

template ENJINSDK_EXPORT project::GetWallet&
BalanceFragmentArguments<project::GetWallet>::set_bal_index_format(models::AssetIndexFormat bal_index_format);

template ENJINSDK_EXPORT project::GetWallet&
BalanceFragmentArguments<project::GetWallet>::set_with_bal_project_uuid();

template ENJINSDK_EXPORT project::GetWallet&
BalanceFragmentArguments<project::GetWallet>::set_with_bal_wallet_address();

// endregion BalanceFragmentArguments

// region TransactionFragmentArguments

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_meta();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_encoded_data();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_asset_data();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_signed_txs();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_error();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_nonce();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_state();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_receipt();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_log_event();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT project::GetWallet&
TransactionFragmentArguments<project::GetWallet>::set_with_transaction_wallet_address();

// endregion TransactionFragmentArguments

// region WalletFragmentArguments

template ENJINSDK_EXPORT project::GetWallet&
WalletFragmentArguments<project::GetWallet>::set_wallet_balance_filter(models::BalanceFilter filter);

template ENJINSDK_EXPORT project::GetWallet&
WalletFragmentArguments<project::GetWallet>::set_with_assets_created();

template ENJINSDK_EXPORT project::GetWallet&
WalletFragmentArguments<project::GetWallet>::set_with_wallet_balances();

template ENJINSDK_EXPORT project::GetWallet&
WalletFragmentArguments<project::GetWallet>::set_with_wallet_transactions();

// endregion WalletFragmentArguments

}

#endif //ENJINCPPSDK_PROJECTGETWALLET_HPP
