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

    std::future<graphql::GraphqlResponse<models::Request>>
    advanced_send_asset_async(AdvancedSendAsset& request) override;

    graphql::GraphqlResponse<models::Request> advanced_send_asset_sync(AdvancedSendAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj_async(ApproveEnj& request) override;

    graphql::GraphqlResponse<models::Request> approve_enj_sync(ApproveEnj& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj_max_async(ApproveMaxEnj& request) override;

    graphql::GraphqlResponse<models::Request> approve_enj_max_sync(ApproveMaxEnj& request) override;

    std::future<graphql::GraphqlResponse<models::Player>> get_player_async(GetPlayer& request) override;

    graphql::GraphqlResponse<models::Player> get_player_sync(GetPlayer& request) override;

    std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet_async(GetWallet& request) override;

    graphql::GraphqlResponse<models::Wallet> get_wallet_sync(GetWallet& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> melt_asset_async(MeltAsset& request) override;

    graphql::GraphqlResponse<models::Request> melt_asset_sync(MeltAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> message_async(Message& request) override;

    graphql::GraphqlResponse<models::Request> message_sync(Message& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> reset_enj_approval_async(ResetEnjApproval& request) override;

    graphql::GraphqlResponse<models::Request> reset_enj_approval_sync(ResetEnjApproval& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_asset_async(SendAsset& request) override;

    graphql::GraphqlResponse<models::Request> send_asset_sync(SendAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_enj_async(SendEnj& request) override;

    graphql::GraphqlResponse<models::Request> send_enj_sync(SendEnj& request) override;

    std::future<graphql::GraphqlResponse<models::Request>>
    set_approval_for_all_async(SetApprovalForAll& request) override;

    graphql::GraphqlResponse<models::Request> set_approval_for_all_sync(SetApprovalForAll& request) override;

    std::future<graphql::GraphqlResponse<bool>> unlink_wallet_async(UnlinkWallet& request) override;

    graphql::GraphqlResponse<bool> unlink_wallet_sync(UnlinkWallet& request) override;

protected:
    /// \brief Constructs the schema with the middleware.
    /// \param middleware The middleware.
    /// \param logger_provider The logger provider.
    explicit PlayerSchema(TrustedPlatformMiddleware middleware,
                          std::shared_ptr<utils::LoggerProvider> logger_provider);
};

}

#endif //ENJINCPPSDK_PLAYERSCHEMA_HPP
