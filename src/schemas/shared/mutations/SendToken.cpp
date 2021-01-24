#include "enjinsdk/shared/SendToken.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

SendToken::SendToken() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.SendToken") {
}

std::string SendToken::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (recipient_address.has_value()) {
        utils::set_string_member(document, "recipientAddress", recipient_address.value());
    }
    if (token_id.has_value()) {
        utils::set_string_member(document, "tokenId", token_id.value());
    }
    if (token_index.has_value()) {
        utils::set_string_member(document, "tokenIndex", token_index.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, "value", value.value());
    }
    if (data.has_value()) {
        utils::set_string_member(document, "data", data.value());
    }

    return utils::document_to_string(document);
}

SendToken& SendToken::set_recipient_address(const std::string& recipient_address) {
    SendToken::recipient_address = recipient_address;
    return *this;
}

SendToken& SendToken::set_token_id(const std::string& token_id) {
    SendToken::token_id = token_id;
    return *this;
}

SendToken& SendToken::set_token_index(const std::string& token_index) {
    SendToken::token_index = token_index;
    return *this;
}

SendToken& SendToken::set_value(const std::string& value) {
    SendToken::value = value;
    return *this;
}

SendToken& SendToken::set_data(const std::string& data) {
    SendToken::data = data;
    return *this;
}

bool SendToken::operator==(const SendToken& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArgumentsTemplate<SendToken>&>(*this) ==
           static_cast<const TransactionRequestArgumentsTemplate<SendToken>&>(rhs) &&
           recipient_address == rhs.recipient_address &&
           token_id == rhs.token_id &&
           token_index == rhs.token_index &&
           value == rhs.value &&
           data == rhs.data;
}

bool SendToken::operator!=(const SendToken& rhs) const {
    return !(rhs == *this);
}

}
