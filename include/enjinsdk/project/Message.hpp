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

#ifndef ENJINCPPSDK_PROJECTMESSAGE_HPP
#define ENJINCPPSDK_PROJECTMESSAGE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request to sign a message to prove wallet ownership.
class ENJINSDK_EXPORT Message : public graphql::AbstractGraphqlRequest,
                                public ProjectTransactionRequestArguments<Message> {
public:
    /// \brief Default constructor.
    Message();

    ~Message() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the message to sign.
    /// \param message The message.
    /// \return This request for chaining.
    Message& set_message(const std::string& message);

    bool operator==(const Message& rhs) const;

    bool operator!=(const Message& rhs) const;

private:
    std::optional<std::string> message;
};

template ENJINSDK_EXPORT Message&
ProjectTransactionRequestArguments<Message>::set_eth_address(const std::string& address);

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_meta();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_encoded_data();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_asset_data();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_signed_txs();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_error();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_nonce();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_state();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_receipt();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_log_event();

template ENJINSDK_EXPORT project::Message&
TransactionFragmentArguments<project::Message>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT project::Message&
TransactionRequestArguments<project::Message>::set_send(bool send);

}

#endif //ENJINCPPSDK_PROJECTMESSAGE_HPP
