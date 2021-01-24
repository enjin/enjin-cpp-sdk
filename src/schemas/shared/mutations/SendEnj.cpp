#include "enjinsdk/shared/SendEnj.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

SendEnj::SendEnj() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.SendEnj") {
}

std::string SendEnj::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (recipient_address.has_value()) {
        utils::set_string_member(document, "recipientAddress", recipient_address.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, "value", value.value());
    }

    return utils::document_to_string(document);
}

SendEnj& SendEnj::set_recipient_address(const std::string& recipient_address) {
    SendEnj::recipient_address = recipient_address;
    return *this;
}

SendEnj& SendEnj::set_value(const std::string& value) {
    SendEnj::value = value;
    return *this;
}

bool SendEnj::operator==(const SendEnj& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArgumentsTemplate<SendEnj>&>(*this) ==
           static_cast<const TransactionRequestArgumentsTemplate<SendEnj>&>(rhs) &&
           recipient_address == rhs.recipient_address &&
           value == rhs.value;
}

bool SendEnj::operator!=(const SendEnj& rhs) const {
    return !(rhs == *this);
}

}
