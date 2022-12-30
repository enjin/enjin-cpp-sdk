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

#ifndef ENJINSDK_UPDATENAME_HPP
#define ENJINSDK_UPDATENAME_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting the name of an existing asset.
class ENJINSDK_EXPORT UpdateName : public graphql::AbstractGraphqlRequest,
                                   public TransactionRequestArguments<UpdateName> {
public:
    /// \brief Default constructor.
    UpdateName();

    ~UpdateName() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the ID of the asset to be updated.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    UpdateName& set_asset_id(std::string asset_id);

    /// \brief Sets the name the asset will be updated to.
    /// \param name The name.
    /// \return This request for chaining.
    UpdateName& set_name(std::string name);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const UpdateName& rhs) const;

    bool operator!=(const UpdateName& rhs) const;

private:
    std::optional<std::string> asset_id_opt;
    std::optional<std::string> name_opt;
};

// region TransactionRequestArguments

template ENJINSDK_EXPORT UpdateName&
TransactionRequestArguments<UpdateName>::set_eth_address(std::string address);

// endregion TransactionRequestArguments

}

namespace enjin::sdk::shared {

// region TransactionFragmentArguments

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_meta();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_encoded_data();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_asset_data();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_signed_txs();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_error();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_nonce();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_state();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_receipt();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_log_event();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT project::UpdateName&
TransactionFragmentArguments<project::UpdateName>::set_with_transaction_wallet_address();

// endregion TransactionFragmentArguments

}

#endif //ENJINSDK_UPDATENAME_HPP
