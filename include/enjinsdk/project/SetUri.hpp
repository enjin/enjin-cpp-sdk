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

#ifndef ENJINCPPSDK_PROJECTSETURI_HPP
#define ENJINCPPSDK_PROJECTSETURI_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request to set the metadata URI of an asset.
class ENJINSDK_EXPORT SetUri : public graphql::AbstractGraphqlRequest,
                               public ProjectTransactionRequestArguments<SetUri> {
public:
    /// \brief Default constructor.
    SetUri();

    ~SetUri() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SetUri& set_asset_id(const std::string& asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    SetUri& set_asset_index(const std::string& asset_index);

    /// \brief Sets the new URI for the asset's metadata.
    /// \param uri The URI.
    /// \return This request for chaining.
    SetUri& set_uri(const std::string& uri);

    bool operator==(const SetUri& rhs) const;

    bool operator!=(const SetUri& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> uri;
};

template ENJINSDK_EXPORT SetUri&
ProjectTransactionRequestArguments<SetUri>::set_eth_address(const std::string& address);

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_meta();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_encoded_data();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_asset_data();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_signed_txs();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_error();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_nonce();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_state();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_receipt();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::SetUri& TransactionFragmentArguments<project::SetUri>::set_with_log_event();

template ENJINSDK_EXPORT project::SetUri&
TransactionFragmentArguments<project::SetUri>::set_with_transaction_project_uuid();

}

#endif //ENJINCPPSDK_PROJECTSETURI_HPP
