#include "enjinsdk/shared/Message.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

Message::Message() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.Message") {
}

std::string Message::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (message.has_value()) {
        utils::set_string_member(document, "message", message.value());
    }

    return utils::document_to_string(document);
}

Message& Message::set_message(const std::string& message) {
    Message::message = message;
    return *this;
}

bool Message::operator==(const Message& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArguments<Message>&>(*this) ==
           static_cast<const TransactionRequestArguments<Message>&>(rhs) &&
           message == rhs.message;
}

bool Message::operator!=(const Message& rhs) const {
    return !(rhs == *this);
}

}
