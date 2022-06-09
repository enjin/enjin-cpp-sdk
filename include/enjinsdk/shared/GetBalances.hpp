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

#ifndef ENJINCPPSDK_SHAREDGETBALANCES_HPP
#define ENJINCPPSDK_SHAREDGETBALANCES_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/BalanceFilter.hpp"
#include "enjinsdk/shared/BalanceFragmentArguments.hpp"
#include "enjinsdk/shared/PaginationArguments.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for getting balances on the platform.
class ENJINSDK_EXPORT GetBalances : public graphql::AbstractGraphqlRequest,
                                    public BalanceFragmentArguments<GetBalances>,
                                    public PaginationArguments<GetBalances> {
public:
    /// \brief Default constructor.
    GetBalances();

    ~GetBalances() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the balance filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetBalances& set_filter(models::BalanceFilter filter);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const GetBalances& rhs) const;

    bool operator!=(const GetBalances& rhs) const;

private:
    std::optional<models::BalanceFilter> filter_opt;
};

// region BalanceFragmentArguments

template ENJINSDK_EXPORT GetBalances&
BalanceFragmentArguments<GetBalances>::set_bal_id_format(models::AssetIdFormat bal_id_format);

template ENJINSDK_EXPORT GetBalances&
BalanceFragmentArguments<GetBalances>::set_bal_index_format(models::AssetIndexFormat bal_index_format);

template ENJINSDK_EXPORT GetBalances&
BalanceFragmentArguments<GetBalances>::set_with_bal_project_uuid();

template ENJINSDK_EXPORT GetBalances&
BalanceFragmentArguments<GetBalances>::set_with_bal_wallet_address();

// endregion BalanceFragmentArguments

// region PaginationArguments

template ENJINSDK_EXPORT GetBalances&
PaginationArguments<GetBalances>::set_pagination(models::PaginationInput pagination);

template ENJINSDK_EXPORT GetBalances&
PaginationArguments<GetBalances>::set_pagination(int page, int limit);

// endregion PaginationArguments

}

#endif //ENJINCPPSDK_SHAREDGETBALANCES_HPP
