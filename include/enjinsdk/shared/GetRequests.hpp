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

#ifndef ENJINCPPSDK_SHAREDGETREQUESTS_HPP
#define ENJINCPPSDK_SHAREDGETREQUESTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/TransactionFilter.hpp"
#include "enjinsdk/models/TransactionSort.hpp"
#include "enjinsdk/shared/PaginationArguments.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for getting transactions on the platform.
class ENJINSDK_EXPORT GetRequests : public graphql::AbstractGraphqlRequest,
                                    public TransactionFragmentArguments<GetRequests>,
                                    public PaginationArguments<GetRequests> {
public:
    /// \brief Default constructor.
    GetRequests();

    ~GetRequests() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetRequests& set_filter(const models::TransactionFilter& filter);

    /// Sets the request to sort the results by the specified options.
    /// \param sort The sort options.
    /// \return This request for chaining.
    GetRequests& set_sort(const models::TransactionSort& sort);

    bool operator==(const GetRequests& rhs) const;

    bool operator!=(const GetRequests& rhs) const;

private:
    std::optional<models::TransactionFilter> filter;
    std::optional<models::TransactionSort> sort;
};

template ENJINSDK_EXPORT GetRequests&
TransactionFragmentArguments<GetRequests>::set_asset_id_format(models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_blockchain_data();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_meta();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_encoded_data();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_asset_data();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_signed_txs();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_error();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_nonce();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_state();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_receipt();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_receipt_logs();

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_log_event();

template ENJINSDK_EXPORT GetRequests&
PaginationArguments<GetRequests>::set_pagination(models::PaginationOptions pagination);

template ENJINSDK_EXPORT GetRequests& PaginationArguments<GetRequests>::set_pagination(int page, int limit);

template ENJINSDK_EXPORT GetRequests& TransactionFragmentArguments<GetRequests>::set_with_transaction_project_uuid();

}

#endif //ENJINCPPSDK_SHAREDGETREQUESTS_HPP
