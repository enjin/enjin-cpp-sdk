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

#ifndef ENJINSDK_PLAYERBRIDGECLAIMASSET_HPP
#define ENJINSDK_PLAYERBRIDGECLAIMASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::player {

/// \brief Request for claiming assets on the bridge.
class ENJINSDK_EXPORT BridgeClaimAsset : public graphql::AbstractGraphqlRequest,
                                         public shared::TransactionFragmentArguments<BridgeClaimAsset> {
public:
    /// \brief Sole constructor.
    BridgeClaimAsset();

    ~BridgeClaimAsset() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets which assets to filter for by their ID.
    /// \param asset_id The asset IDs to filter for.
    /// \return This request for chaining.
    BridgeClaimAsset& set_asset_id(std::string asset_id);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const BridgeClaimAsset& rhs) const;

    bool operator!=(const BridgeClaimAsset& rhs) const;

private:
    std::optional<std::string> asset_id_opt;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_blockchain_data();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_meta();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_encoded_data();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_asset_data();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_signed_txs();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_error();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_nonce();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_state();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_receipt();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_receipt_logs();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_log_event();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT player::BridgeClaimAsset&
TransactionFragmentArguments<player::BridgeClaimAsset>::set_with_transaction_wallet_address();

}

#endif //ENJINSDK_PLAYERBRIDGECLAIMASSET_HPP
