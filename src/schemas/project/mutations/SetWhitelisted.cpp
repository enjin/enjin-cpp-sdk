#include "enjinsdk/project/SetWhitelisted.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetWhitelisted::SetWhitelisted() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetWhitelisted") {
}

std::string SetWhitelisted::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (token_id.has_value()) {
        utils::set_string_member(document, "tokenId", token_id.value());
    }
    if (account_address.has_value()) {
        utils::set_string_member(document, "accountAddress", account_address.value());
    }
    if (whitelisted.has_value()) {
        utils::set_string_member(document, "whitelisted", utils::serialize_whitelisted(whitelisted.value()));
    }
    if (whitelisted_address.has_value()) {
        utils::set_string_member(document, "whitelistedAddress", whitelisted_address.value());
    }
    if (on.has_value()) {
        utils::set_boolean_member(document, "on", on.value());
    }

    return utils::document_to_string(document);
}

SetWhitelisted& SetWhitelisted::set_token_id(const std::string& token_id) {
    SetWhitelisted::token_id = token_id;
    return *this;
}

SetWhitelisted& SetWhitelisted::set_account_address(const std::string& account_address) {
    SetWhitelisted::account_address = account_address;
    return *this;
}

SetWhitelisted& SetWhitelisted::set_whitelisted(models::Whitelisted whitelisted) {
    SetWhitelisted::whitelisted = whitelisted;
    return *this;
}

SetWhitelisted& SetWhitelisted::set_whitelisted_address(const std::string& whitelisted_address) {
    SetWhitelisted::whitelisted_address = whitelisted_address;
    return *this;
}

SetWhitelisted& SetWhitelisted::set_on(bool on) {
    SetWhitelisted::on = on;
    return *this;
}

bool SetWhitelisted::operator==(const SetWhitelisted& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetWhitelisted>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetWhitelisted>&>(rhs) &&
           token_id == rhs.token_id &&
           account_address == rhs.account_address &&
           whitelisted == rhs.whitelisted &&
           whitelisted_address == rhs.whitelisted_address &&
           on == rhs.on;
}

bool SetWhitelisted::operator!=(const SetWhitelisted& rhs) const {
    return !(rhs == *this);
}

}
