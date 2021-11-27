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

#ifndef ENJINCPPSDK_PLAYERMESSAGE_HPP
#define ENJINCPPSDK_PLAYERMESSAGE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::player {

/// \brief Request to sign a message to prove wallet ownership.
class ENJINSDK_EXPORT Message : public graphql::AbstractGraphqlRequest,
                                public shared::TransactionFragmentArguments<Message> {
public:
    /// \brief Default constructor.
    Message();

    ~Message() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the message to sign.
    /// \param message The message.
    /// \return This request for chaining.
    Message& set_message(std::string message);

    bool operator==(const Message& rhs) const;

    bool operator!=(const Message& rhs) const;

private:
    std::optional<std::string> message;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_transaction_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_blockchain_data();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_meta();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_encoded_data();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_asset_data();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_signed_txs();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_error();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_nonce();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_state();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_receipt();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_receipt_logs();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_log_event();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT player::Message&
TransactionFragmentArguments<player::Message>::set_with_transaction_wallet_address();

}

#endif //ENJINCPPSDK_PLAYERMESSAGE_HPP
