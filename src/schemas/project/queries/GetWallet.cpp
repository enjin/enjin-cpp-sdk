#include "enjinsdk/project/GetWallet.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

GetWallet::GetWallet() : graphql::AbstractGraphqlRequest("enjin.sdk.project.GetWallet") {
}

std::string GetWallet::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, WalletFragmentArguments::serialize());

    if (user_id.has_value()) {
        utils::set_string_member(document, "userId", user_id.value());
    }
    if (eth_address.has_value()) {
        utils::set_string_member(document, "ethAddress", eth_address.value());
    }

    return utils::document_to_string(document);
}

GetWallet& GetWallet::set_user_id(const std::string& user_id) {
    GetWallet::user_id = user_id;
    return *this;
}

GetWallet& GetWallet::set_eth_address(const std::string& eth_address) {
    GetWallet::eth_address = eth_address;
    return *this;
}

bool GetWallet::operator==(const GetWallet& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::WalletFragmentArguments<GetWallet>&>(*this) ==
           static_cast<const shared::WalletFragmentArguments<GetWallet>&>(rhs) &&
           user_id == rhs.user_id &&
           eth_address == rhs.eth_address;
}

bool GetWallet::operator!=(const GetWallet& rhs) const {
    return !(rhs == *this);
}

}
