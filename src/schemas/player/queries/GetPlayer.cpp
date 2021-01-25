#include "enjinsdk/player/GetPlayer.hpp"

namespace enjin::sdk::player {

GetPlayer::GetPlayer() : graphql::AbstractGraphqlRequest("enjin.sdk.player.GetPlayer") {
}

std::string GetPlayer::serialize() {
    return PlayerFragmentArgumentsTemplate::serialize();
}

bool GetPlayer::operator==(const GetPlayer& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::PlayerFragmentArgumentsTemplate<GetPlayer>&>(*this) ==
           static_cast<const shared::PlayerFragmentArgumentsTemplate<GetPlayer>&>(rhs);
}

bool GetPlayer::operator!=(const GetPlayer& rhs) const {
    return !(rhs == *this);
}

}
