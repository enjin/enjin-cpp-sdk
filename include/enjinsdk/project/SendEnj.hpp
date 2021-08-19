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

#ifndef ENJINCPPSDK_PROJECTSENDENJ_HPP
#define ENJINCPPSDK_PROJECTSENDENJ_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for sending send ENJ.
class ENJINSDK_EXPORT SendEnj : public graphql::AbstractGraphqlRequest,
                                public ProjectTransactionRequestArguments<SendEnj> {
public:
    /// \brief Default constructor.
    SendEnj();

    ~SendEnj() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    SendEnj& set_recipient_address(const std::string& recipient_address);

    /// \brief Sets the amount of ENJ to send.
    /// \param value The value.
    /// \return This request for chaining.
    /// \remarks The value is in Wei as 10^18 (e.g. 1 ENJ = 1000000000000000000).
    SendEnj& set_value(const std::string& value);

    bool operator==(const SendEnj& rhs) const;

    bool operator!=(const SendEnj& rhs) const;

private:
    std::optional<std::string> recipient_address;
    std::optional<std::string> value;
};

template ENJINSDK_EXPORT SendEnj&
ProjectTransactionRequestArguments<SendEnj>::set_eth_address(const std::string& address);

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_meta();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_encoded_data();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_asset_data();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_signed_txs();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_error();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_nonce();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_state();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_receipt();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::SendEnj&
TransactionFragmentArguments<project::SendEnj>::set_with_log_event();

template ENJINSDK_EXPORT project::SendEnj&
TransactionRequestArguments<project::SendEnj>::set_send(bool send);

}

#endif //ENJINCPPSDK_PROJECTSENDENJ_HPP
