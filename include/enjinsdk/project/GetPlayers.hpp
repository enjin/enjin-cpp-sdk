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

#ifndef ENJINCPPSDK_PROJECTGETPLAYERS_HPP
#define ENJINCPPSDK_PROJECTGETPLAYERS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/PlayerFilter.hpp"
#include "enjinsdk/shared/PaginationArguments.hpp"
#include "enjinsdk/shared/PlayerFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for getting players on the platform.
class ENJINSDK_EXPORT GetPlayers : public graphql::AbstractGraphqlRequest,
                                   public shared::PlayerFragmentArguments<GetPlayers>,
                                   public shared::PaginationArguments<GetPlayers> {
public:
    /// \brief Default constructor.
    GetPlayers();

    ~GetPlayers() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetPlayers& set_filter(const models::PlayerFilter& filter);

    bool operator==(const GetPlayers& rhs) const;

    bool operator!=(const GetPlayers& rhs) const;

private:
    std::optional<models::PlayerFilter> filter;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::GetPlayers& PlayerFragmentArguments<project::GetPlayers>::set_with_linking_info();

template ENJINSDK_EXPORT project::GetPlayers& PlayerFragmentArguments<project::GetPlayers>::set_qr_size(int size);

template ENJINSDK_EXPORT project::GetPlayers& PlayerFragmentArguments<project::GetPlayers>::set_with_wallet();

template ENJINSDK_EXPORT project::GetPlayers& WalletFragmentArguments<project::GetPlayers>::set_with_assets_created();

template ENJINSDK_EXPORT project::GetPlayers&
PaginationArguments<project::GetPlayers>::set_pagination(models::PaginationOptions pagination);

template ENJINSDK_EXPORT project::GetPlayers&
PaginationArguments<project::GetPlayers>::set_pagination(int page, int limit);

}

#endif //ENJINCPPSDK_PROJECTGETPLAYERS_HPP
