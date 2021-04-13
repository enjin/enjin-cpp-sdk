#include "enjinsdk/player/UnlinkWallet.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::player {

UnlinkWallet::UnlinkWallet() : graphql::AbstractGraphqlRequest("enjin.sdk.player.UnlinkWallet") {
}

std::string UnlinkWallet::serialize() const {
    return utils::document_to_string(rapidjson::Document(rapidjson::kObjectType));
}

bool UnlinkWallet::operator==(const UnlinkWallet& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs);
}

bool UnlinkWallet::operator!=(const UnlinkWallet& rhs) const {
    return !(rhs == *this);
}

}
