#include "enjinsdk/internal/TransactionRequestArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string TransactionRequestArgumentsImpl::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionFragmentArgumentsImpl::serialize());

    if (eth_address.has_value()) {
        utils::set_string_member(document, "ethAddress", eth_address.value());
    }
    if (send.has_value()) {
        utils::set_boolean_member(document, "send", send.value());
    }

    return utils::document_to_string(document);
}

void TransactionRequestArgumentsImpl::set_eth_address(const std::string& address) {
    TransactionRequestArgumentsImpl::eth_address = address;
}

void TransactionRequestArgumentsImpl::set_send(bool send) {
    TransactionRequestArgumentsImpl::send = send;
}

bool TransactionRequestArgumentsImpl::operator==(const TransactionRequestArgumentsImpl& rhs) const {
    return static_cast<const TransactionFragmentArgumentsImpl&>(*this) ==
           static_cast<const TransactionFragmentArgumentsImpl&>(rhs) &&
           eth_address == rhs.eth_address &&
           send == rhs.send;
}

bool TransactionRequestArgumentsImpl::operator!=(const TransactionRequestArgumentsImpl& rhs) const {
    return !(rhs == *this);
}

}
