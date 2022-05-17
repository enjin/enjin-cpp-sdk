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

#ifndef ENJINCPPSDK_PROJECTRELEASERESERVE_HPP
#define ENJINCPPSDK_PROJECTRELEASERESERVE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for releasing the reserve of an asset.
class ENJINSDK_EXPORT ReleaseReserve : public graphql::AbstractGraphqlRequest,
                                       public ProjectTransactionRequestArguments<ReleaseReserve> {
public:
    /// \brief Default constructor.
    ReleaseReserve();

    ~ReleaseReserve() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    ReleaseReserve& set_asset_id(const std::string& asset_id);

    /// \brief Sets the amount to release.
    /// \param value The amount.
    /// \return This request for chaining.
    ReleaseReserve& set_value(const std::string& value);

    bool operator==(const ReleaseReserve& rhs) const;

    bool operator!=(const ReleaseReserve& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> value;
};

template ENJINSDK_EXPORT ReleaseReserve&
ProjectTransactionRequestArguments<ReleaseReserve>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_blockchain_data();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_meta();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_encoded_data();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_asset_data();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_signed_txs();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_error();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_nonce();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_state();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_receipt();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_receipt_logs();

template ENJINSDK_EXPORT ReleaseReserve& ProjectTransactionRequestArguments<ReleaseReserve>::set_with_log_event();

template ENJINSDK_EXPORT ReleaseReserve&
ProjectTransactionRequestArguments<ReleaseReserve>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT ReleaseReserve&
ProjectTransactionRequestArguments<ReleaseReserve>::set_eth_address(const std::string& address);

}

#endif //ENJINCPPSDK_PROJECTRELEASERESERVE_HPP
