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

#ifndef ENJINCPPSDK_PROJECTSETTRANSFERABLE_HPP
#define ENJINCPPSDK_PROJECTSETTRANSFERABLE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/AssetTransferable.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting if a asset may be transferred.
class ENJINSDK_EXPORT SetTransferable : public graphql::AbstractGraphqlRequest,
                                        public ProjectTransactionRequestArguments<SetTransferable> {
public:
    /// \brief Default constructor.
    SetTransferable();

    ~SetTransferable() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SetTransferable& set_asset_id(std::string asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    SetTransferable& set_asset_index(std::string asset_index);

    /// \brief Sets the new transfer mode.
    /// \param transferable The new mode.
    /// \return This request for chaining.
    SetTransferable& set_transferable(models::AssetTransferable transferable);

    bool operator==(const SetTransferable& rhs) const;

    bool operator!=(const SetTransferable& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<models::AssetTransferable> transferable;
};

template ENJINSDK_EXPORT SetTransferable&
ProjectTransactionRequestArguments<SetTransferable>::set_eth_address(std::string address);

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_meta();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_encoded_data();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_asset_data();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_signed_txs();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_error();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_nonce();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_state();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_receipt();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_log_event();

template ENJINSDK_EXPORT project::SetTransferable&
TransactionFragmentArguments<project::SetTransferable>::set_with_transaction_project_uuid();

}

#endif //ENJINCPPSDK_PROJECTSETTRANSFERABLE_HPP
