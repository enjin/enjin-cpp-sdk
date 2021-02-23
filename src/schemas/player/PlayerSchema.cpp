#include "enjinsdk/player/PlayerSchema.hpp"

#include <utility>

namespace enjin::sdk::player {

PlayerSchema::PlayerSchema(TrustedPlatformMiddleware middleware)
        : shared::SharedSchema(std::move(middleware), "player") {
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
