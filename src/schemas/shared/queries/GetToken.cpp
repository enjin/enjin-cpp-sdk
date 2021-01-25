#include "enjinsdk/shared/GetToken.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetToken::GetToken() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetToken") {
}

std::string GetToken::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TokenFragmentArgumentsTemplate::serialize());

    if (id.has_value()) {
        utils::set_string_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

GetToken& GetToken::set_id(const std::string& id) {
    GetToken::id = id;
    return *this;
}

bool GetToken::operator==(const GetToken& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TokenFragmentArgumentsTemplate<GetToken>&>(*this) ==
           static_cast<const TokenFragmentArgumentsTemplate<GetToken>&>(rhs) &&
           id == rhs.id;
}

bool GetToken::operator!=(const GetToken& rhs) const {
    return !(rhs == *this);
}

}
