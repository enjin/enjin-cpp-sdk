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

#ifndef ENJINSDK_PROJECTBRIDGEASSET_HPP
#define ENJINSDK_PROJECTBRIDGEASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for bridging an asset.
class ENJINSDK_EXPORT BridgeAsset : public graphql::AbstractGraphqlRequest,
                                    public ProjectTransactionRequestArguments<BridgeAsset> {
public:
    /// \brief Sole constructor.
    BridgeAsset();

    ~BridgeAsset() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the ID of the asset to bridge.
    /// \param asset_id The asset ID.
    /// \return This request for chaining.
    BridgeAsset& set_asset_id(std::string asset_id);

    /// \brief Sets the index of the asset to bridge if the asset is an NFT.
    /// \param asset_index The asset index.
    /// \return This request for chaining.
    BridgeAsset& set_asset_index(std::string asset_index);

    /// \brief Sets the amount to bridge.
    /// \param value The amount.
    /// \return This request for chaining.
    BridgeAsset& set_value(std::string value);

    bool operator==(const BridgeAsset& rhs) const;

    bool operator!=(const BridgeAsset& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> value;
};

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_blockchain_data();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_meta();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_encoded_data();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_asset_data();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_signed_txs();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_error();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_nonce();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_state();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_receipt();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_receipt_logs();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_log_event();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT BridgeAsset&
ProjectTransactionRequestArguments<BridgeAsset>::set_eth_address(const std::string& address);

}

#endif //ENJINSDK_PROJECTBRIDGEASSET_HPP
