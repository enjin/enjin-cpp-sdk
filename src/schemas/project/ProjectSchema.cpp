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

#include "enjinsdk/project/ProjectSchema.hpp"

#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;

ProjectSchema::ProjectSchema(std::unique_ptr<http::IHttpClient> http_client,
                             std::shared_ptr<utils::LoggerProvider> logger_provider)
        : shared::SharedSchema(std::move(http_client), "project", std::move(logger_provider)) {
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::advanced_send_asset(AdvancedSendAsset request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::approve_enj(ApproveEnj request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::approve_enj_max(ApproveMaxEnj request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<AccessToken>> ProjectSchema::auth_player(AuthPlayer request) {
    return send_request_for_one<AccessToken>(request);
}

std::future<GraphqlResponse<AccessToken>> ProjectSchema::auth_project(AuthProject request) {
    return send_request_for_one<AccessToken>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::bridge_asset(BridgeAsset request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::bridge_assets(BridgeAssets request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::bridge_claim_asset(BridgeClaimAsset request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::complete_trade(CompleteTrade request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::create_asset(CreateAsset request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<AccessToken>> ProjectSchema::create_player(CreatePlayer request) {
    return send_request_for_one<AccessToken>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::create_trade(CreateTrade request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::decrease_max_melt_fee(DecreaseMaxMeltFee request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::decrease_max_transfer_fee(DecreaseMaxTransferFee request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<bool>> ProjectSchema::delete_player(DeletePlayer request) {
    return send_request_for_one<bool>(request);
}

std::future<GraphqlResponse<std::vector<Asset>>>
ProjectSchema::get_assets_from_projects(GetAssetsFromProjects request) {
    return send_request_for_many<Asset>(request);
}

std::future<GraphqlResponse<Player>> ProjectSchema::get_player(GetPlayer request) {
    return send_request_for_one<Player>(request);
}

std::future<GraphqlResponse<std::vector<Player>>> ProjectSchema::get_players(GetPlayers request) {
    return send_request_for_many<Player>(request);
}

std::future<GraphqlResponse<Wallet>> ProjectSchema::get_wallet(GetWallet request) {
    return send_request_for_one<Wallet>(request);
}

std::future<GraphqlResponse<std::vector<Wallet>>> ProjectSchema::get_wallets(GetWallets request) {
    return send_request_for_many<Wallet>(request);
}

std::future<GraphqlResponse<bool>> ProjectSchema::invalidate_asset_metadata(InvalidateAssetMetadata request) {
    return send_request_for_one<bool>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::melt_asset(MeltAsset request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::message(Message request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::mint_asset(MintAsset request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::release_reserve(ReleaseReserve request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::reset_enj_approval(ResetEnjApproval request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::send_asset(SendAsset request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::send_enj(SendEnj request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::set_approval_for_all(SetApprovalForAll request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::set_melt_fee(SetMeltFee request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::set_transfer_fee(SetTransferFee request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::set_transferable(SetTransferable request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::set_uri(SetUri request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::set_whitelisted(SetWhitelisted request) {
    return send_request_for_one<Transaction>(request);
}

std::future<GraphqlResponse<bool>> ProjectSchema::unlink_wallet(UnlinkWallet request) {
    return send_request_for_one<bool>(request);
}

std::future<GraphqlResponse<Transaction>> ProjectSchema::update_name(UpdateName request) {
    return send_request_for_one<Transaction>(request);
}
