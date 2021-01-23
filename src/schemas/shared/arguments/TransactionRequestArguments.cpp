#include "enjinsdk/internal/TransactionRequestArguments.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string TransactionRequestArguments::serialize() {
    rapidjson::Document document;
    document.Parse(TransactionFragmentArguments::serialize().c_str());

    if (eth_address.has_value()) {
        utils::set_string_member(document, "ethAddress", eth_address.value());
    }
    if (test.has_value()) {
        utils::set_boolean_member(document, "test", test.value());
    }
    if (send.has_value()) {
        utils::set_boolean_member(document, "send", send.value());
    }

    return utils::document_to_string(document);
}

void TransactionRequestArguments::set_eth_address(const std::string& address) {
    TransactionRequestArguments::eth_address = address;
}

void TransactionRequestArguments::set_test(bool test) {
    TransactionRequestArguments::test = test;
}

void TransactionRequestArguments::set_send(bool send) {
    TransactionRequestArguments::send = send;
}

bool TransactionRequestArguments::operator==(const TransactionRequestArguments& rhs) const {
    return eth_address == rhs.eth_address &&
           test == rhs.test &&
           send == rhs.send;
}

bool TransactionRequestArguments::operator!=(const TransactionRequestArguments& rhs) const {
    return !(rhs == *this);
}

}
