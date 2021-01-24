#include "enjinsdk/shared/SetApprovalForAll.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

SetApprovalForAll::SetApprovalForAll() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.SetApprovalForAll") {
}

std::string SetApprovalForAll::serialize() {
    rapidjson::Document document;
    document.Parse(TransactionRequestArgumentsTemplate::serialize().c_str());

    if (operator_address.has_value()) {
        utils::set_string_member(document, "operatorAddress", operator_address.value());
    }
    if (approved.has_value()) {
        utils::set_boolean_member(document, "approved", approved.value());
    }

    return utils::document_to_string(document);
}

SetApprovalForAll& SetApprovalForAll::set_operator_address(const std::string& operator_address) {
    SetApprovalForAll::operator_address = operator_address;
    return *this;
}

SetApprovalForAll& SetApprovalForAll::set_approved(bool approved) {
    SetApprovalForAll::approved = approved;
    return *this;
}

bool SetApprovalForAll::operator==(const SetApprovalForAll& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArgumentsTemplate<SetApprovalForAll>&>(*this) ==
           static_cast<const TransactionRequestArgumentsTemplate<SetApprovalForAll>&>(rhs) &&
           operator_address == rhs.operator_address &&
           approved == rhs.approved;
}

bool SetApprovalForAll::operator!=(const SetApprovalForAll& rhs) const {
    return !(rhs == *this);
}

}
