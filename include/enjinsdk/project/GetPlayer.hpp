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

#ifndef ENJINCPPSDK_PROJECTGETPLAYER_HPP
#define ENJINCPPSDK_PROJECTGETPLAYER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/PlayerFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for getting a player on the platform.
class ENJINSDK_EXPORT GetPlayer : public graphql::AbstractGraphqlRequest,
                                  public shared::PlayerFragmentArguments<GetPlayer> {
public:
    /// \brief Default constructor.
    GetPlayer();

    ~GetPlayer() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the player ID.
    /// \param id The ID.
    /// \return This request for chaining.
    GetPlayer& set_id(std::string id);

    bool operator==(const GetPlayer& rhs) const;

    bool operator!=(const GetPlayer& rhs) const;

private:
    std::optional<std::string> id;
};

}

namespace enjin::sdk::shared {

// AssetFragmentArguments functions

template ENJINSDK_EXPORT project::GetPlayer&
PlayerFragmentArguments<project::GetPlayer>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_state_data();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_config_data();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_asset_blocks();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_creator();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_melt_details();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_metadata_uri();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_supply_details();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_transfer_settings();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_asset_variant_mode();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_asset_variants();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_variant_metadata();

// PlayerFragmentArguments functions

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_linking_info();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_qr_size(int size);

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_wallet();

// TransactionFragmentArguments functions

template ENJINSDK_EXPORT project::GetPlayer&
PlayerFragmentArguments<project::GetPlayer>::set_transaction_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_meta();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_encoded_data();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_asset_data();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_signed_txs();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_error();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_nonce();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_state();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_receipt();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_log_event();

template ENJINSDK_EXPORT project::GetPlayer&
PlayerFragmentArguments<project::GetPlayer>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT project::GetPlayer&
PlayerFragmentArguments<project::GetPlayer>::set_with_transaction_wallet_address();

// WalletFragmentArguments functions

template ENJINSDK_EXPORT project::GetPlayer&
PlayerFragmentArguments<project::GetPlayer>::set_wallet_balance_filter(models::BalanceFilter filter);

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_assets_created();

template ENJINSDK_EXPORT project::GetPlayer& PlayerFragmentArguments<project::GetPlayer>::set_with_wallet_balances();

template ENJINSDK_EXPORT project::GetPlayer&
PlayerFragmentArguments<project::GetPlayer>::set_with_wallet_transactions();

}

#endif //ENJINCPPSDK_PROJECTGETPLAYER_HPP
