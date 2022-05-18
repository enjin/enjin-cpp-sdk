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

    PlayerSchema(const PlayerSchema&) = delete;

    PlayerSchema(PlayerSchema&& rhs) = delete;

    ~PlayerSchema() override = default;

    std::future<graphql::GraphqlResponse<models::Request>> advanced_send_asset(AdvancedSendAsset request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj(ApproveEnj request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj_max(ApproveMaxEnj request) override;

    std::future<graphql::GraphqlResponse<models::Request>> bridge_asset(BridgeAsset request) override;

    std::future<graphql::GraphqlResponse<models::Request>> bridge_assets(BridgeAssets request) override;

    std::future<graphql::GraphqlResponse<models::Request>> bridge_claim_asset(BridgeClaimAsset request) override;

    std::future<graphql::GraphqlResponse<models::Player>> get_player(GetPlayer request) override;

    std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet(GetWallet request) override;

    std::future<graphql::GraphqlResponse<models::Request>> melt_asset(MeltAsset request) override;

    std::future<graphql::GraphqlResponse<models::Request>> message(Message request) override;

    std::future<graphql::GraphqlResponse<models::Request>> reset_enj_approval(ResetEnjApproval request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_asset(SendAsset request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_enj(SendEnj request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_approval_for_all(SetApprovalForAll request) override;

    std::future<graphql::GraphqlResponse<bool>> unlink_wallet(UnlinkWallet request) override;

protected:
    /// \brief Constructs an instance of this class.
    /// \param http_client The HTTP client.
    /// \param logger_provider The logger provider.
    PlayerSchema(std::unique_ptr<http::IHttpClient> http_client,
                 std::shared_ptr<utils::LoggerProvider> logger_provider);
};

}

#endif //ENJINCPPSDK_PLAYERSCHEMA_HPP
