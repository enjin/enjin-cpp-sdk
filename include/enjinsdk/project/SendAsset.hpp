/* Copyright 2021 Enjin Pte Ltd.
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

#ifndef ENJINCPPSDK_PROJECTSENDASSET_HPP
#define ENJINCPPSDK_PROJECTSENDASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for sending a asset.
class ENJINSDK_EXPORT SendAsset : public graphql::AbstractGraphqlRequest,
                                  public ProjectTransactionRequestArguments<SendAsset> {
public:
    /// \brief Default constructor.
    SendAsset();

    ~SendAsset() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    SendAsset& set_recipient_address(const std::string& recipient_address);

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SendAsset& set_asset_id(const std::string& asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    SendAsset& set_asset_index(const std::string& asset_index);

    /// \brief Sets the amount to send.
    /// \param value The amount.
    /// \return This request for chaining.
    SendAsset& set_value(const std::string& value);

    /// \brief Sets the data to forward with the transaction.
    /// \param data The data.
    /// \return This request for chaining.
    SendAsset& set_data(const std::string& data);

    bool operator==(const SendAsset& rhs) const;

    bool operator!=(const SendAsset& rhs) const;

private:
    std::optional<std::string> recipient_address;
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> value;
    std::optional<std::string> data;
};

template ENJINSDK_EXPORT SendAsset&
ProjectTransactionRequestArguments<SendAsset>::set_eth_address(const std::string& address);

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_meta();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_encoded_data();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_asset_data();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_signed_txs();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_error();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_nonce();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_state();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_receipt();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::SendAsset&
TransactionFragmentArguments<project::SendAsset>::set_with_log_event();

template ENJINSDK_EXPORT project::SendAsset&
TransactionRequestArguments<project::SendAsset>::set_send(bool send);

}

#endif //ENJINCPPSDK_PROJECTSENDASSET_HPP
