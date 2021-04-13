#include "enjinsdk/player/GetPlayer.hpp"

namespace enjin::sdk::player {

GetPlayer::GetPlayer() : graphql::AbstractGraphqlRequest("enjin.sdk.player.GetPlayer") {
}

std::string GetPlayer::serialize() const {
    return PlayerFragmentArguments::serialize();
}

bool GetPlayer::operator==(const GetPlayer& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::PlayerFragmentArguments<GetPlayer>&>(*this) ==
           static_cast<const shared::PlayerFragmentArguments<GetPlayer>&>(rhs);
}

bool GetPlayer::operator!=(const GetPlayer& rhs) const {
    return !(rhs == *this);
}

}
