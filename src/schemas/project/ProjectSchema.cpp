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

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::advanced_send_asset(AdvancedSendAsset& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::approve_enj(ApproveEnj& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::approve_enj_max(ApproveMaxEnj& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::AccessToken>> ProjectSchema::auth_player(AuthPlayer& request) {
    return send_request_for_one<models::AccessToken>(request);
}

std::future<graphql::GraphqlResponse<models::AccessToken>> ProjectSchema::auth_project(AuthProject& request) {
    return send_request_for_one<models::AccessToken>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::complete_trade(CompleteTrade& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::create_asset(CreateAsset& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::AccessToken>> ProjectSchema::create_player(CreatePlayer& request) {
    return send_request_for_one<models::AccessToken>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::create_trade(CreateTrade& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>>
ProjectSchema::decrease_max_melt_fee(DecreaseMaxMeltFee& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>>
ProjectSchema::decrease_max_transfer_fee(DecreaseMaxTransferFee& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<bool>> ProjectSchema::delete_player(DeletePlayer& request) {
    return send_request_for_one<bool>(request);
}

std::future<graphql::GraphqlResponse<models::Player>> ProjectSchema::get_player(GetPlayer& request) {
    return send_request_for_one<models::Player>(request);
}

std::future<graphql::GraphqlResponse<std::vector<models::Player>>> ProjectSchema::get_players(GetPlayers& request) {
    return send_request_for_many<models::Player>(request);
}

std::future<graphql::GraphqlResponse<models::Wallet>> ProjectSchema::get_wallet(GetWallet& request) {
    return send_request_for_one<models::Wallet>(request);
}

std::future<graphql::GraphqlResponse<std::vector<models::Wallet>>> ProjectSchema::get_wallets(GetWallets& request) {
    return send_request_for_many<models::Wallet>(request);
}

std::future<graphql::GraphqlResponse<bool>> ProjectSchema::invalidate_asset_metadata(InvalidateAssetMetadata& request) {
    return send_request_for_one<bool>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::melt_asset(MeltAsset& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::message(Message& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::mint_asset(MintAsset& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::release_reserve(ReleaseReserve& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::reset_enj_approval(ResetEnjApproval& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::send_asset(SendAsset& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::send_enj(SendEnj& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_approval_for_all(SetApprovalForAll& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_melt_fee(SetMeltFee& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_transfer_fee(SetTransferFee& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_transferable(SetTransferable& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_uri(SetUri& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<models::Request>> ProjectSchema::set_whitelisted(SetWhitelisted& request) {
    return send_request_for_one<models::Request>(request);
}

std::future<graphql::GraphqlResponse<bool>> ProjectSchema::unlink_wallet(UnlinkWallet& request) {
    return send_request_for_one<bool>(request);
}

}
