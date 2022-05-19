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

#ifndef ENJINCPPSDK_PROJECTSETWHITELISTED_HPP
#define ENJINCPPSDK_PROJECTSETWHITELISTED_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Whitelisted.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting an asset's whitelist.
class ENJINSDK_EXPORT SetWhitelisted : public graphql::AbstractGraphqlRequest,
                                       public ProjectTransactionRequestArguments<SetWhitelisted> {
public:
    /// \brief Default constructor.
    SetWhitelisted();

    ~SetWhitelisted() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SetWhitelisted& set_asset_id(const std::string& asset_id);

    /// \brief Sets the account address to be added to the whitelist.
    /// \param account_address The address.
    /// \return This request for chaining.
    SetWhitelisted& set_account_address(const std::string& account_address);

    /// \brief Sets the whitelisted setting for the account.
    /// \param whitelisted The setting.
    /// \return This request for chaining.
    SetWhitelisted& set_whitelisted(models::Whitelisted whitelisted);

    /// \brief Sets the specified address for sending or receiving.
    /// \param whitelisted_address The address.
    /// \return This request for chaining.
    SetWhitelisted& set_whitelisted_address(const std::string& whitelisted_address);

    /// \brief Sets whether the whitelist setting is on or off.
    /// \param on The setting.
    /// \return This request for chaining.
    SetWhitelisted& set_on(bool on);

    bool operator==(const SetWhitelisted& rhs) const;

    bool operator!=(const SetWhitelisted& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> account_address;
    std::optional<models::Whitelisted> whitelisted;
    std::optional<std::string> whitelisted_address;
    std::optional<bool> on;
};

template ENJINSDK_EXPORT project::SetWhitelisted&
ProjectTransactionRequestArguments<project::SetWhitelisted>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::SetWhitelisted&
ProjectTransactionRequestArguments<project::SetWhitelisted>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::SetWhitelisted&
ProjectTransactionRequestArguments<project::SetWhitelisted>::set_with_meta();

template ENJINSDK_EXPORT project::SetWhitelisted&
ProjectTransactionRequestArguments<project::SetWhitelisted>::set_with_encoded_data();

template ENJINSDK_EXPORT project::SetWhitelisted&
ProjectTransactionRequestArguments<project::SetWhitelisted>::set_with_asset_data();

template ENJINSDK_EXPORT project::SetWhitelisted&
ProjectTransactionRequestArguments<project::SetWhitelisted>::set_with_signed_txs();

template ENJINSDK_EXPORT SetWhitelisted&
ProjectTransactionRequestArguments<SetWhitelisted>::set_with_error();

template ENJINSDK_EXPORT SetWhitelisted&
ProjectTransactionRequestArguments<SetWhitelisted>::set_with_nonce();

template ENJINSDK_EXPORT SetWhitelisted&
ProjectTransactionRequestArguments<SetWhitelisted>::set_with_state();

template ENJINSDK_EXPORT SetWhitelisted&
ProjectTransactionRequestArguments<SetWhitelisted>::set_with_receipt();

template ENJINSDK_EXPORT SetWhitelisted&
ProjectTransactionRequestArguments<SetWhitelisted>::set_with_receipt_logs();

template ENJINSDK_EXPORT SetWhitelisted&
ProjectTransactionRequestArguments<SetWhitelisted>::set_with_log_event();

template ENJINSDK_EXPORT SetWhitelisted&
ProjectTransactionRequestArguments<SetWhitelisted>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT SetWhitelisted&
ProjectTransactionRequestArguments<SetWhitelisted>::set_eth_address(const std::string& address);

}

#endif //ENJINCPPSDK_PROJECTSETWHITELISTED_HPP
