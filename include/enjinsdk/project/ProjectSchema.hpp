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

    ~ProjectSchema() override = default;

    std::future<graphql::GraphqlResponse<models::Request>> advanced_send_asset(AdvancedSendAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj(ApproveEnj& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj_max(ApproveMaxEnj& request) override;

    std::future<graphql::GraphqlResponse<models::AccessToken>> auth_player(AuthPlayer& request) override;

    std::future<graphql::GraphqlResponse<models::AccessToken>> auth_project(AuthProject& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> bridge_asset(BridgeAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> bridge_assets(BridgeAssets& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> bridge_claim_asset(BridgeClaimAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> complete_trade(CompleteTrade& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> create_asset(CreateAsset& request) override;

    std::future<graphql::GraphqlResponse<models::AccessToken>> create_player(CreatePlayer& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> create_trade(CreateTrade& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> decrease_max_melt_fee(DecreaseMaxMeltFee& request) override;

    std::future<graphql::GraphqlResponse<models::Request>>
    decrease_max_transfer_fee(DecreaseMaxTransferFee& request) override;

    std::future<graphql::GraphqlResponse<bool>> delete_player(DeletePlayer& request) override;

    std::future<graphql::GraphqlResponse<models::Player>> get_player(GetPlayer& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Player>>> get_players(GetPlayers& request) override;

    std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet(GetWallet& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Wallet>>> get_wallets(GetWallets& request) override;

    std::future<graphql::GraphqlResponse<bool>> invalidate_asset_metadata(InvalidateAssetMetadata& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> melt_asset(MeltAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> message(Message& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> mint_asset(MintAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> release_reserve(ReleaseReserve& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> reset_enj_approval(ResetEnjApproval& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_asset(SendAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_enj(SendEnj& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_approval_for_all(SetApprovalForAll& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_melt_fee(SetMeltFee& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_transfer_fee(SetTransferFee& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_transferable(SetTransferable& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_uri(SetUri& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_whitelisted(SetWhitelisted& request) override;

    std::future<graphql::GraphqlResponse<bool>> unlink_wallet(UnlinkWallet& request) override;

protected:
    /// \brief Constructs the schema with the middleware.
    /// \param middleware The middleware.
    /// \param logger_provider The logger provider.
    explicit ProjectSchema(TrustedPlatformMiddleware middleware,
                           std::shared_ptr<utils::LoggerProvider> logger_provider);

    /// \brief Move constructor.
    /// \param rhs The schema being moved.
    ProjectSchema(ProjectSchema&& rhs) = default;
};

}

#endif //ENJINCPPSDK_PROJECTSCHEMA_HPP
