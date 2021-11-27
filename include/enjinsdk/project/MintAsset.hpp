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

#ifndef ENJINCPPSDK_PROJECTMINTASSET_HPP
#define ENJINCPPSDK_PROJECTMINTASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/MintInput.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for minting a asset.
class ENJINSDK_EXPORT MintAsset : public graphql::AbstractGraphqlRequest,
                                  public ProjectTransactionRequestArguments<MintAsset> {
public:
    /// \brief Default constructor.
    MintAsset();

    ~MintAsset() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    MintAsset& set_asset_id(std::string asset_id);

    /// \brief Sets the mints to be performed.
    /// \param mints The mints.
    /// \return This request for chaining.
    MintAsset& set_mints(std::vector<models::MintInput> mints);

    bool operator==(const MintAsset& rhs) const;

    bool operator!=(const MintAsset& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::vector<models::MintInput>> mints;
};

template ENJINSDK_EXPORT MintAsset&
ProjectTransactionRequestArguments<MintAsset>::set_transaction_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_blockchain_data();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_meta();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_encoded_data();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_asset_data();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_signed_txs();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_error();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_nonce();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_state();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_receipt();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_receipt_logs();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_log_event();

template ENJINSDK_EXPORT MintAsset& ProjectTransactionRequestArguments<MintAsset>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT MintAsset&
ProjectTransactionRequestArguments<MintAsset>::set_with_transaction_wallet_address();

template ENJINSDK_EXPORT MintAsset&
ProjectTransactionRequestArguments<MintAsset>::set_eth_address(std::string address);

}

#endif //ENJINCPPSDK_PROJECTMINTASSET_HPP
