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

#include "enjinsdk/project/ProjectSchema.hpp"

#include <utility>

namespace enjin::sdk::project {

ProjectSchema::ProjectSchema(TrustedPlatformMiddleware middleware,
                             std::shared_ptr<utils::LoggerProvider> logger_provider)
        : shared::SharedSchema(std::move(middleware), "project", std::move(logger_provider)) {
}

std::future<graphql::GraphqlResponse<models::Request>>
ProjectSchema::advanced_send_asset_async(AdvancedSendAsset& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::advanced_send_asset_sync(AdvancedSendAsset& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::approve_enj_async(ApproveEnj& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::approve_enj_sync(ApproveEnj& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::approve_enj_max_async(ApproveMaxEnj& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::approve_enj_max_sync(ApproveMaxEnj& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::AccessToken>> ProjectSchema::auth_player_async(AuthPlayer& request) {
    return send_request_for_one<models::AccessToken>(request);
}

graphql::GraphqlResponse<models::AccessToken> ProjectSchema::auth_player_sync(AuthPlayer& request) {
    return send_request_for_one<models::AccessToken>(request).get();
}

std::future<graphql::GraphqlResponse<models::AccessToken>> ProjectSchema::auth_project_async(AuthProject& request) {
    return send_request_for_one<models::AccessToken>(request);
}

graphql::GraphqlResponse<models::AccessToken> ProjectSchema::auth_project_sync(AuthProject& request) {
    return send_request_for_one<models::AccessToken>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::complete_trade_async(CompleteTrade& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::complete_trade_sync(CompleteTrade& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::create_asset_async(CreateAsset& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::create_asset_sync(CreateAsset& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::create_player_async(CreatePlayer& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::create_player_sync(CreatePlayer& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::create_trade_async(CreateTrade& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::create_trade_sync(CreateTrade& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>>
ProjectSchema::decrease_max_melt_fee_async(DecreaseMaxMeltFee& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::decrease_max_melt_fee_sync(DecreaseMaxMeltFee& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>>
ProjectSchema::decrease_max_transfer_fee_async(DecreaseMaxTransferFee& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request>
ProjectSchema::decrease_max_transfer_fee_sync(DecreaseMaxTransferFee& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<bool>> ProjectSchema::delete_player_async(DeletePlayer& request) {
    return send_request_for_one<bool>(request);
}

graphql::GraphqlResponse<bool> ProjectSchema::delete_player_sync(DeletePlayer& request) {
    return send_request_for_one<bool>(request).get();
}

std::future<graphql::GraphqlResponse<models::Player>> ProjectSchema::get_player_async(GetPlayer& request) {
    return send_request_for_one<models::Player>(request);
}

graphql::GraphqlResponse<models::Player> ProjectSchema::get_player_sync(GetPlayer& request) {
    return send_request_for_one<models::Player>(request).get();
}

std::future<graphql::GraphqlResponse<std::vector<models::Player>>>
ProjectSchema::get_players_async(GetPlayers& request) {
    return send_request_for_many<models::Player>(request);
}

graphql::GraphqlResponse<std::vector<models::Player>> ProjectSchema::get_players_sync(GetPlayers& request) {
    return send_request_for_many<models::Player>(request).get();
}

std::future<graphql::GraphqlResponse<models::Wallet>> ProjectSchema::get_wallet_async(GetWallet& request) {
    return send_request_for_one<models::Wallet>(request);
}

graphql::GraphqlResponse<models::Wallet> ProjectSchema::get_wallet_sync(GetWallet& request) {
    return send_request_for_one<models::Wallet>(request).get();
}

std::future<graphql::GraphqlResponse<std::vector<models::Wallet>>>
ProjectSchema::get_wallets_async(GetWallets& request) {
    return send_request_for_many<models::Wallet>(request);
}

graphql::GraphqlResponse<std::vector<models::Wallet>> ProjectSchema::get_wallets_sync(GetWallets& request) {
    return send_request_for_many<models::Wallet>(request).get();
}

std::future<graphql::GraphqlResponse<bool>>
ProjectSchema::invalidate_asset_metadata_async(InvalidateAssetMetadata& request) {
    return send_request_for_one<bool>(request);
}

graphql::GraphqlResponse<bool> ProjectSchema::invalidate_asset_metadata_sync(InvalidateAssetMetadata& request) {
    return send_request_for_one<bool>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::melt_asset_async(MeltAsset& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::melt_asset_sync(MeltAsset& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::message_async(Message& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::message_sync(Message& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::mint_asset_async(MintAsset& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::mint_asset_sync(MintAsset& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::release_reserve_async(ReleaseReserve& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::release_reserve_sync(ReleaseReserve& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>>
ProjectSchema::reset_enj_approval_async(ResetEnjApproval& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::reset_enj_approval_sync(ResetEnjApproval& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::send_asset_async(SendAsset& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::send_asset_sync(SendAsset& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::send_enj_async(SendEnj& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::send_enj_sync(SendEnj& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>>
ProjectSchema::set_approval_for_all_async(SetApprovalForAll& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::set_approval_for_all_sync(SetApprovalForAll& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_melt_fee_async(SetMeltFee& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::set_melt_fee_sync(SetMeltFee& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_transfer_fee_async(SetTransferFee& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::set_transfer_fee_sync(SetTransferFee& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_transferable_async(SetTransferable& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::set_transferable_sync(SetTransferable& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_uri_async(SetUri& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::set_uri_sync(SetUri& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_whitelisted_async(SetWhitelisted& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> ProjectSchema::set_whitelisted_sync(SetWhitelisted& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<bool>> ProjectSchema::unlink_wallet_async(UnlinkWallet& request) {
    return send_request_for_one<bool>(request);
}

graphql::GraphqlResponse<bool> ProjectSchema::unlink_wallet_sync(UnlinkWallet& request) {
    return send_request_for_one<bool>(request).get();
}

}
