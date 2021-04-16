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

#ifndef ENJINCPPSDK_PLAYERSCHEMA_HPP
#define ENJINCPPSDK_PLAYERSCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/player/IPlayerSchema.hpp"
#include "enjinsdk/shared/SharedSchema.hpp"

namespace enjin::sdk::player {

/// \brief Class for sending requests in the player schema.
class ENJINSDK_EXPORT PlayerSchema : public IPlayerSchema,
                                     public shared::SharedSchema {
public:
    PlayerSchema() = delete;

    ~PlayerSchema() override = default;

    std::future<graphql::GraphqlResponse<models::Player>> get_player_async(GetPlayer& request) override;

    graphql::GraphqlResponse<models::Player> get_player_sync(GetPlayer& request) override;

    std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet_async(GetWallet& request) override;

    graphql::GraphqlResponse<models::Wallet> get_wallet_sync(GetWallet& request) override;

    std::future<graphql::GraphqlResponse<bool>> unlink_wallet_async(UnlinkWallet& request) override;

    graphql::GraphqlResponse<bool> unlink_wallet_sync(UnlinkWallet& request) override;

protected:
    /// \brief Constructs the schema with the middleware.
    /// \param middleware The middleware.
    /// \param logger The logger.
    explicit PlayerSchema(TrustedPlatformMiddleware middleware, std::shared_ptr<utils::Logger> logger);
};

}

#endif //ENJINCPPSDK_PLAYERSCHEMA_HPP
