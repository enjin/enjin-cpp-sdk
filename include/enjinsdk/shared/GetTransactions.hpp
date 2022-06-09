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

#ifndef ENJINCPPSDK_SHAREDGETTRANSACTIONS_HPP
#define ENJINCPPSDK_SHAREDGETTRANSACTIONS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/TransactionFilter.hpp"
#include "enjinsdk/models/TransactionSortInput.hpp"
#include "enjinsdk/shared/PaginationArguments.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for getting transactions on the platform.
class ENJINSDK_EXPORT GetTransactions : public graphql::AbstractGraphqlRequest,
                                        public TransactionFragmentArguments<GetTransactions>,
                                        public PaginationArguments<GetTransactions> {
public:
    /// \brief Default constructor.
    GetTransactions();

    ~GetTransactions() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetTransactions& set_filter(models::TransactionFilter filter);

    /// Sets the request to sort the results by the specified options.
    /// \param sort The sort input.
    /// \return This request for chaining.
    GetTransactions& set_sort(models::TransactionSortInput sort);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const GetTransactions& rhs) const;

    bool operator!=(const GetTransactions& rhs) const;

private:
    std::optional<models::TransactionFilter> filter_opt;
    std::optional<models::TransactionSortInput> sort_opt;
};

// region TransactionFragmentArguments

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_transaction_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_blockchain_data();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_meta();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_encoded_data();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_asset_data();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_signed_txs();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_error();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_nonce();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_state();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_receipt();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_receipt_logs();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_log_event();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT GetTransactions&
TransactionFragmentArguments<GetTransactions>::set_with_transaction_wallet_address();

// endregion TransactionFragmentArguments

// region PaginationArguments

template ENJINSDK_EXPORT GetTransactions&
PaginationArguments<GetTransactions>::set_pagination(models::PaginationInput pagination);

template ENJINSDK_EXPORT GetTransactions&
PaginationArguments<GetTransactions>::set_pagination(int page, int limit);

// endregion PaginationArguments

}

#endif //ENJINCPPSDK_SHAREDGETTRANSACTIONS_HPP
