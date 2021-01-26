#include "enjinsdk/project/SetUri.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetUri::SetUri() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetUri") {
}

std::string SetUri::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (token_id.has_value()) {
        utils::set_string_member(document, "tokenId", token_id.value());
    }
    if (token_index.has_value()) {
        utils::set_string_member(document, "tokenIndex", token_index.value());
    }
    if (uri.has_value()) {
        utils::set_string_member(document, "uri", uri.value());
    }

    return utils::document_to_string(document);
}

SetUri& SetUri::set_token_id(const std::string& token_id) {
    SetUri::token_id = token_id;
    return *this;
}

SetUri& SetUri::set_token_index(const std::string& token_index) {
    SetUri::token_index = token_index;
    return *this;
}

SetUri& SetUri::set_uri(const std::string& uri) {
    SetUri::uri = uri;
    return *this;
}

bool SetUri::operator==(const SetUri& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetUri>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetUri>&>(rhs) &&
           token_id == rhs.token_id &&
           token_index == rhs.token_index &&
           uri == rhs.uri;
}

bool SetUri::operator!=(const SetUri& rhs) const {
    return !(rhs == *this);
}

}
