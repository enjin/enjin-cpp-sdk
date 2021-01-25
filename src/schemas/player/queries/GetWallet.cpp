#include "enjinsdk/player/GetWallet.hpp"

namespace enjin::sdk::player {

GetWallet::GetWallet() : graphql::AbstractGraphqlRequest("enjin.sdk.player.GetWallet") {
}

std::string GetWallet::serialize() {
    return WalletFragmentArgumentsTemplate::serialize();
}

bool GetWallet::operator==(const GetWallet& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::WalletFragmentArgumentsTemplate<GetWallet>&>(*this) ==
           static_cast<const shared::WalletFragmentArgumentsTemplate<GetWallet>&>(rhs);
}

bool GetWallet::operator!=(const GetWallet& rhs) const {
    return !(rhs == *this);
}

}
