#include "enjinsdk/project/InvalidateTokenMetadata.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

InvalidateTokenMetadata::InvalidateTokenMetadata()
        : graphql::AbstractGraphqlRequest("enjin.sdk.project.InvalidateTokenMetadata") {
}

std::string InvalidateTokenMetadata::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (id.has_value()) {
        utils::set_string_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

InvalidateTokenMetadata& InvalidateTokenMetadata::set_id(const std::string& id) {
    InvalidateTokenMetadata::id = id;
    return *this;
}

bool InvalidateTokenMetadata::operator==(const InvalidateTokenMetadata& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           id == rhs.id;
}

bool InvalidateTokenMetadata::operator!=(const InvalidateTokenMetadata& rhs) const {
    return !(rhs == *this);
}

}
