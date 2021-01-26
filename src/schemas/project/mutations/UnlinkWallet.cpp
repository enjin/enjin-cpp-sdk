#include "enjinsdk/project/UnlinkWallet.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

UnlinkWallet::UnlinkWallet() : graphql::AbstractGraphqlRequest("enjin.sdk.project.UnlinkWallet") {
}

std::string UnlinkWallet::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (eth_address.has_value()) {
        utils::set_string_member(document, "ethAddress", eth_address.value());
    }

    return utils::document_to_string(document);
}

UnlinkWallet& UnlinkWallet::set_eth_address(const std::string& eth_address) {
    UnlinkWallet::eth_address = eth_address;
    return *this;
}

bool UnlinkWallet::operator==(const UnlinkWallet& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           eth_address == rhs.eth_address;
}

bool UnlinkWallet::operator!=(const UnlinkWallet& rhs) const {
    return !(rhs == *this);
}

}
