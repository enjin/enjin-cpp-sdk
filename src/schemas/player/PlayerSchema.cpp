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

#include "enjinsdk/player/PlayerSchema.hpp"

#include <utility>

namespace enjin::sdk::player {

PlayerSchema::PlayerSchema(TrustedPlatformMiddleware middleware,
                           std::shared_ptr<utils::LoggerProvider> logger_provider)
        : shared::SharedSchema(std::move(middleware), "player", std::move(logger_provider)) {
}

std::future<graphql::GraphqlResponse<models::Player>> PlayerSchema::get_player_async(GetPlayer& request) {
    return send_request_for_one<models::Player>(request);
}

graphql::GraphqlResponse<models::Player> PlayerSchema::get_player_sync(GetPlayer& request) {
    return send_request_for_one<models::Player>(request).get();
}

std::future<graphql::GraphqlResponse<models::Wallet>> PlayerSchema::get_wallet_async(GetWallet& request) {
    return send_request_for_one<models::Wallet>(request);
}

graphql::GraphqlResponse<models::Wallet> PlayerSchema::get_wallet_sync(GetWallet& request) {
    return send_request_for_one<models::Wallet>(request).get();
}

std::future<graphql::GraphqlResponse<bool>> PlayerSchema::unlink_wallet_async(UnlinkWallet& request) {
    return send_request_for_one<bool>(request);
}

graphql::GraphqlResponse<bool> PlayerSchema::unlink_wallet_sync(UnlinkWallet& request) {
    return send_request_for_one<bool>(request).get();
}

}
