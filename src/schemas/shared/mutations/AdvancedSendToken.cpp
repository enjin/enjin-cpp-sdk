#include "enjinsdk/shared/AdvancedSendToken.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

AdvancedSendToken::AdvancedSendToken() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.AdvancedSendToken") {
}

std::string AdvancedSendToken::serialize() {
    rapidjson::Document document;
    document.Parse(TransactionRequestArgumentsTemplate::serialize().c_str());

    if (transfers.has_value()) {
        utils::set_array_member_from_type_vector<models::Transfer>(document, "transfers", transfers.value());
    }
    if (data.has_value()) {
        utils::set_string_member(document, "data", data.value());
    }

    return utils::document_to_string(document);
}

AdvancedSendToken& AdvancedSendToken::set_transfers(const std::vector<models::Transfer>& transfers) {
    AdvancedSendToken::transfers = transfers;
    return *this;
}

AdvancedSendToken& AdvancedSendToken::set_data(const std::string& data) {
    AdvancedSendToken::data = data;
    return *this;
}

bool AdvancedSendToken::operator==(const AdvancedSendToken& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArgumentsTemplate<AdvancedSendToken>&>(*this) ==
           static_cast<const TransactionRequestArgumentsTemplate<AdvancedSendToken>&>(rhs) &&
           transfers == rhs.transfers &&
           data == rhs.data;
}

bool AdvancedSendToken::operator!=(const AdvancedSendToken& rhs) const {
    return !(rhs == *this);
}

}
