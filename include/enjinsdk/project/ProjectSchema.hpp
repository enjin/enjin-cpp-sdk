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

#ifndef ENJINCPPSDK_PROJECTSCHEMA_HPP
#define ENJINCPPSDK_PROJECTSCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/project/IProjectSchema.hpp"
#include "enjinsdk/shared/SharedSchema.hpp"

namespace enjin::sdk::project {

/// \brief Class for sending requests in the project schema.
class ENJINSDK_EXPORT ProjectSchema : public IProjectSchema,
                                      public shared::SharedSchema {
public:
    ProjectSchema() = delete;

    ProjectSchema(const ProjectSchema&) = delete;

    ProjectSchema(ProjectSchema&& rhs) = delete;

    ~ProjectSchema() override = default;

    std::future<graphql::GraphqlResponse<models::Transaction>> advanced_send_asset(AdvancedSendAsset request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> approve_enj(ApproveEnj request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> approve_enj_max(ApproveMaxEnj request) override;

    std::future<graphql::GraphqlResponse<models::AccessToken>> auth_player(AuthPlayer request) override;

    std::future<graphql::GraphqlResponse<models::AccessToken>> auth_project(AuthProject request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> bridge_asset(BridgeAsset request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> bridge_assets(BridgeAssets request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> bridge_claim_asset(BridgeClaimAsset request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> complete_trade(CompleteTrade request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> create_asset(CreateAsset request) override;

    std::future<graphql::GraphqlResponse<models::AccessToken>> create_player(CreatePlayer request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> create_trade(CreateTrade request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> decrease_max_melt_fee(DecreaseMaxMeltFee request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>>
    decrease_max_transfer_fee(DecreaseMaxTransferFee request) override;

    std::future<graphql::GraphqlResponse<bool>> delete_player(DeletePlayer request) override;

    std::future<graphql::GraphqlResponse<models::Player>> get_player(GetPlayer request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Player>>> get_players(GetPlayers request) override;

    std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet(GetWallet request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Wallet>>> get_wallets(GetWallets request) override;

    std::future<graphql::GraphqlResponse<bool>> invalidate_asset_metadata(InvalidateAssetMetadata request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> melt_asset(MeltAsset request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> message(Message request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> mint_asset(MintAsset request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> release_reserve(ReleaseReserve request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> reset_enj_approval(ResetEnjApproval request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> send_asset(SendAsset request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> send_enj(SendEnj request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> set_approval_for_all(SetApprovalForAll request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> set_melt_fee(SetMeltFee request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> set_transfer_fee(SetTransferFee request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> set_transferable(SetTransferable request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> set_uri(SetUri request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> set_whitelisted(SetWhitelisted request) override;

    std::future<graphql::GraphqlResponse<bool>> unlink_wallet(UnlinkWallet request) override;

    std::future<graphql::GraphqlResponse<models::Transaction>> update_name(UpdateName request) override;

protected:
    /// \brief Constructs an instance of this class.
    /// \param http_client The HTTP client.
    /// \param logger_provider The logger provider.
    ProjectSchema(std::unique_ptr<http::IHttpClient> http_client,
                  std::shared_ptr<utils::LoggerProvider> logger_provider);
};

}

#endif //ENJINCPPSDK_PROJECTSCHEMA_HPP
