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

#ifndef ENJINCPPSDK_PLAYERSENDENJ_HPP
#define ENJINCPPSDK_PLAYERSENDENJ_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::player {

/// \brief Request for sending send ENJ.
class ENJINSDK_EXPORT SendEnj : public graphql::AbstractGraphqlRequest,
                                public shared::TransactionFragmentArguments<SendEnj> {
public:
    /// \brief Default constructor.
    SendEnj();

    ~SendEnj() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    SendEnj& set_recipient_address(std::string recipient_address);

    /// \brief Sets the amount of ENJ to send.
    /// \param value The value.
    /// \return This request for chaining.
    /// \remarks The value is in Wei as 10^18 (e.g. 1 ENJ = 1000000000000000000).
    SendEnj& set_value(std::string value);

    bool operator==(const SendEnj& rhs) const;

    bool operator!=(const SendEnj& rhs) const;

private:
    std::optional<std::string> recipient_address;
    std::optional<std::string> value;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_blockchain_data();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_meta();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_encoded_data();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_asset_data();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_signed_txs();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_error();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_nonce();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_state();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_receipt();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_receipt_logs();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_log_event();

template ENJINSDK_EXPORT player::SendEnj&
TransactionFragmentArguments<player::SendEnj>::set_with_transaction_project_uuid();

}

#endif //ENJINCPPSDK_PLAYERSENDENJ_HPP
