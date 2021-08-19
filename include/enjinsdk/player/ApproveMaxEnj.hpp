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

#ifndef ENJINCPPSDK_PLAYERAPPROVEMAXENJ_HPP
#define ENJINCPPSDK_PLAYERAPPROVEMAXENJ_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"

namespace enjin::sdk::player {

/// \brief Request for approving the crypto items contract to spend the maximum amount of ENJ.
class ENJINSDK_EXPORT ApproveMaxEnj : public graphql::AbstractGraphqlRequest,
                                      public shared::TransactionRequestArguments<ApproveMaxEnj> {
public:
    /// \brief Default constructor.
    ApproveMaxEnj();

    ~ApproveMaxEnj() override = default;

    [[nodiscard]] std::string serialize() const override;

    bool operator==(const ApproveMaxEnj& rhs) const;

    bool operator!=(const ApproveMaxEnj& rhs) const;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_blockchain_data();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_meta();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_encoded_data();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_asset_data();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_signed_txs();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_error();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_nonce();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_state();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_receipt();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_receipt_logs();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionFragmentArguments<player::ApproveMaxEnj>::set_with_log_event();

template ENJINSDK_EXPORT player::ApproveMaxEnj&
TransactionRequestArguments<player::ApproveMaxEnj>::set_send(bool send);

}

#endif //ENJINCPPSDK_PLAYERAPPROVEMAXENJ_HPP
