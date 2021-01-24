#include "enjinsdk/shared/CreateTrade.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

CreateTrade::CreateTrade() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.CreateTrade") {

}

std::string CreateTrade::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (asking_tokens.has_value()) {
        utils::set_array_member_from_type_vector<models::Trade>(document, "askingTokens", asking_tokens.value());
    }
    if (offering_tokens.has_value()) {
        utils::set_array_member_from_type_vector<models::Trade>(document, "offeringTokens", offering_tokens.value());
    }
    if (recipient_address.has_value()) {
        utils::set_string_member(document, "recipientAddress", recipient_address.value());
    }

    return utils::document_to_string(document);
}

CreateTrade& CreateTrade::set_asking_tokens(std::vector<models::Trade> tokens) {
    asking_tokens = tokens;
    return *this;
}

CreateTrade& CreateTrade::set_offering_tokens(std::vector<models::Trade> tokens) {
    offering_tokens = tokens;
    return *this;
}

CreateTrade& CreateTrade::set_recipient_address(const std::string& recipient_address) {
    CreateTrade::recipient_address = recipient_address;
    return *this;
}

bool CreateTrade::operator==(const CreateTrade& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArgumentsTemplate<CreateTrade>&>(*this) ==
           static_cast<const TransactionRequestArgumentsTemplate<CreateTrade>&>(rhs) &&
           asking_tokens == rhs.asking_tokens &&
           offering_tokens == rhs.offering_tokens &&
           recipient_address == rhs.recipient_address;
}

bool CreateTrade::operator!=(const CreateTrade& rhs) const {
    return !(rhs == *this);
}

}
