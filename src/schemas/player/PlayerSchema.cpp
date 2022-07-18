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

#include "enjinsdk/player/PlayerSchema.hpp"

#include <utility>

namespace enjin::sdk::player {

PlayerSchema::PlayerSchema(std::unique_ptr<http::IHttpClient> http_client,
                           std::shared_ptr<utils::LoggerProvider> logger_provider)
        : shared::SharedSchema(std::move(http_client), "player", std::move(logger_provider)) {
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::advanced_send_asset(AdvancedSendAsset request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::approve_enj(ApproveEnj request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::approve_enj_max(ApproveMaxEnj request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::bridge_asset(BridgeAsset request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::bridge_assets(BridgeAssets request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::bridge_claim_asset(BridgeClaimAsset request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Player>> PlayerSchema::get_player(GetPlayer request) {
    return send_request_for_one<models::Player>(request);
}

std::future<graphql::GraphqlResponse<models::Wallet>> PlayerSchema::get_wallet(GetWallet request) {
    return send_request_for_one<models::Wallet>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::melt_asset(MeltAsset request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::message(Message request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::reset_enj_approval(ResetEnjApproval request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::send_asset(SendAsset request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::send_enj(SendEnj request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> PlayerSchema::set_approval_for_all(SetApprovalForAll request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<bool>> PlayerSchema::unlink_wallet(UnlinkWallet request) {
    return send_request_for_one<bool>(request);
}

}
