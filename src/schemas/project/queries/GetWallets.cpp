#include "enjinsdk/project/GetWallets.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

GetWallets::GetWallets() : graphql::AbstractGraphqlRequest("enjin.sdk.project.GetWallets") {
}

std::string GetWallets::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_objects_to_document(document, {
            WalletFragmentArguments::serialize(),
            PaginationArguments::serialize()
    });

    if (user_ids.has_value()) {
        utils::set_array_member_from_string_vector(document, "userIds", user_ids.value());
    }
    if (eth_addresses.has_value()) {
        utils::set_array_member_from_string_vector(document, "ethAddresses", eth_addresses.value());
    }

    return utils::document_to_string(document);
}

GetWallets& GetWallets::set_user_ids(const std::vector<std::string>& user_ids) {
    GetWallets::user_ids = user_ids;
    return *this;
}

GetWallets& GetWallets::set_eth_addresses(const std::vector<std::string>& eth_addresses) {
    GetWallets::eth_addresses = eth_addresses;
    return *this;
}

bool GetWallets::operator==(const GetWallets& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::WalletFragmentArguments<GetWallets>&>(*this) ==
           static_cast<const shared::WalletFragmentArguments<GetWallets>&>(rhs) &&
           static_cast<const shared::PaginationArguments<GetWallets>&>(*this) ==
           static_cast<const shared::PaginationArguments<GetWallets>&>(rhs) &&
           user_ids == rhs.user_ids &&
           eth_addresses == rhs.eth_addresses;
}

bool GetWallets::operator!=(const GetWallets& rhs) const {
    return !(rhs == *this);
}

}
