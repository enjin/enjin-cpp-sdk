#include "enjinsdk/project/SetTransferable.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetTransferable::SetTransferable() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetTransferable") {
}

std::string SetTransferable::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (token_id.has_value()) {
        utils::set_string_member(document, "tokenId", token_id.value());
    }
    if (token_index.has_value()) {
        utils::set_string_member(document, "tokenIndex", token_index.value());
    }
    if (transferable.has_value()) {
        utils::set_string_member(document, "transferable", utils::serialize_token_transferable(transferable.value()));
    }

    return utils::document_to_string(document);
}

SetTransferable& SetTransferable::set_token_id(const std::string& token_id) {
    SetTransferable::token_id = token_id;
    return *this;
}

SetTransferable& SetTransferable::set_token_index(const std::string& token_index) {
    SetTransferable::token_index = token_index;
    return *this;
}

SetTransferable& SetTransferable::set_transferable(models::TokenTransferable transferable) {
    SetTransferable::transferable = transferable;
    return *this;
}

bool SetTransferable::operator==(const SetTransferable& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetTransferable>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetTransferable>&>(rhs) &&
           token_id == rhs.token_id &&
           token_index == rhs.token_index &&
           transferable == rhs.transferable;
}

bool SetTransferable::operator!=(const SetTransferable& rhs) const {
    return !(rhs == *this);
}

}
