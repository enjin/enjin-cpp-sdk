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

#ifndef ENJINCPPSDK_PROJECTGETWALLETS_HPP
#define ENJINCPPSDK_PROJECTGETWALLETS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/PaginationArguments.hpp"
#include "enjinsdk/shared/WalletFragmentArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for getting wallets from the platform.
class ENJINSDK_EXPORT GetWallets : public graphql::AbstractGraphqlRequest,
                                   public shared::WalletFragmentArguments<GetWallets>,
                                   public shared::PaginationArguments<GetWallets> {
public:
    /// \brief Default constructor.
    GetWallets();

    ~GetWallets() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the user IDs owning the wallets to get.
    /// \param user_ids The IDs.
    /// \return This request for chaining.
    GetWallets& set_user_ids(const std::vector<std::string>& user_ids);

    /// \brief Sets the Ethereum addresses of the wallets to get.
    /// \param eth_addresses The addresses.
    /// \return This request for chaining.
    GetWallets& set_eth_addresses(const std::vector<std::string>& eth_addresses);

    bool operator==(const GetWallets& rhs) const;

    bool operator!=(const GetWallets& rhs) const;

private:
    std::optional<std::vector<std::string>> user_ids;
    std::optional<std::vector<std::string>> eth_addresses;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::GetWallets& WalletFragmentArguments<project::GetWallets>::set_with_assets_created();

template ENJINSDK_EXPORT project::GetWallets&
PaginationArguments<project::GetWallets>::set_pagination(models::PaginationOptions pagination);

template ENJINSDK_EXPORT project::GetWallets&
PaginationArguments<project::GetWallets>::set_pagination(int page, int limit);

}

#endif //ENJINCPPSDK_PROJECTGETWALLETS_HPP
