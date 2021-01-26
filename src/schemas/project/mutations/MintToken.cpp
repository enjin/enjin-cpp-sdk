#include "enjinsdk/project/MintToken.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

MintToken::MintToken() : graphql::AbstractGraphqlRequest("enjin.sdk.project.MintToken") {
}

std::string MintToken::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (token_id.has_value()) {
        utils::set_string_member(document, "tokenId", token_id.value());
    }
    if (mints.has_value()) {
        utils::set_array_member_from_type_vector<models::MintInput>(document, "mints", mints.value());
    }

    return utils::document_to_string(document);
}

MintToken& MintToken::set_token_id(const std::string& token_id) {
    MintToken::token_id = token_id;
    return *this;
}

MintToken& MintToken::set_mints(const std::vector<models::MintInput>& mints) {
    MintToken::mints = mints;
    return *this;
}

bool MintToken::operator==(const MintToken& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<MintToken>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<MintToken>&>(rhs) &&
           token_id == rhs.token_id &&
           mints == rhs.mints;
}

bool MintToken::operator!=(const MintToken& rhs) const {
    return !(rhs == *this);
}

}
