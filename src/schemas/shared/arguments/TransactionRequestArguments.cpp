#include "enjinsdk/internal/TransactionRequestArguments.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string TransactionRequestArguments::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionFragmentArguments::serialize());

    if (eth_address.has_value()) {
        utils::set_string_member(document, "ethAddress", eth_address.value());
    }
    if (send.has_value()) {
        utils::set_boolean_member(document, "send", send.value());
    }

    return utils::document_to_string(document);
}

void TransactionRequestArguments::set_eth_address(const std::string& address) {
    TransactionRequestArguments::eth_address = address;
}

void TransactionRequestArguments::set_send(bool send) {
    TransactionRequestArguments::send = send;
}

bool TransactionRequestArguments::operator==(const TransactionRequestArguments& rhs) const {
    return static_cast<const TransactionFragmentArguments&>(*this) ==
           static_cast<const TransactionFragmentArguments&>(rhs) &&
           eth_address == rhs.eth_address &&
           send == rhs.send;
}

bool TransactionRequestArguments::operator!=(const TransactionRequestArguments& rhs) const {
    return !(rhs == *this);
}

}
