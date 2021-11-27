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

#ifndef ENJINSDK_PROJECTBRIDGEASSETS_HPP
#define ENJINSDK_PROJECTBRIDGEASSETS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for bridging multiple indices of an NFT in a single transaction.
class ENJINSDK_EXPORT BridgeAssets : public graphql::AbstractGraphqlRequest,
                                     public ProjectTransactionRequestArguments<BridgeAssets> {
public:
    /// \brief Sole constructor.
    BridgeAssets();

    ~BridgeAssets() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the ID of the asset to bridge.
    /// \param asset_id The asset ID.
    /// \return This request for chaining.
    BridgeAssets& set_asset_id(std::string asset_id);

    /// \brief Sets the indices to bridge.
    /// \param asset_indices The asset indices.
    /// \return This request for chaining.
    BridgeAssets& set_asset_indices(std::vector<std::string> asset_indices);

    bool operator==(const BridgeAssets& rhs) const;

    bool operator!=(const BridgeAssets& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::vector<std::string>> asset_indices;
};

template ENJINSDK_EXPORT BridgeAssets&
ProjectTransactionRequestArguments<BridgeAssets>::set_eth_address(std::string address);

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_meta();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_encoded_data();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_asset_data();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_signed_txs();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_error();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_nonce();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_state();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_receipt();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_log_event();

template ENJINSDK_EXPORT project::BridgeAssets&
TransactionFragmentArguments<project::BridgeAssets>::set_with_transaction_project_uuid();

}

#endif //ENJINSDK_PROJECTBRIDGEASSETS_HPP
