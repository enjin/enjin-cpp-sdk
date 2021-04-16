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

#ifndef ENJINCPPSDK_SHAREDSETAPPROVALFORALL_HPP
#define ENJINCPPSDK_SHAREDSETAPPROVALFORALL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

class ENJINSDK_EXPORT SetApprovalForAll : public graphql::AbstractGraphqlRequest,
                                          public TransactionRequestArguments<SetApprovalForAll> {
public:
    SetApprovalForAll();

    ~SetApprovalForAll() override = default;

    [[nodiscard]] std::string serialize() const override;

    SetApprovalForAll& set_operator_address(const std::string& operator_address);

    SetApprovalForAll& set_approved(bool approved);

    bool operator==(const SetApprovalForAll& rhs) const;

    bool operator!=(const SetApprovalForAll& rhs) const;

private:
    std::optional<std::string> operator_address;
    std::optional<bool> approved;
};

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_blockchain_data();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_meta();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_encoded_data();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_asset_data();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_signed_txs();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_error();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_nonce();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_state();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_receipt();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_receipt_logs();

template ENJINSDK_EXPORT SetApprovalForAll& TransactionFragmentArguments<SetApprovalForAll>::set_with_log_event();

template ENJINSDK_EXPORT SetApprovalForAll&
TransactionRequestArguments<SetApprovalForAll>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT SetApprovalForAll& TransactionRequestArguments<SetApprovalForAll>::set_send(bool send);

}

#endif //ENJINCPPSDK_SHAREDSETAPPROVALFORALL_HPP
