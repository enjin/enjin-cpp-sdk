#include "enjinsdk/project/InvalidateAssetMetadata.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

InvalidateAssetMetadata::InvalidateAssetMetadata()
        : graphql::AbstractGraphqlRequest("enjin.sdk.project.InvalidateAssetMetadata") {
}

std::string InvalidateAssetMetadata::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (id.has_value()) {
        utils::set_string_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

InvalidateAssetMetadata& InvalidateAssetMetadata::set_id(const std::string& id) {
    InvalidateAssetMetadata::id = id;
    return *this;
}

bool InvalidateAssetMetadata::operator==(const InvalidateAssetMetadata& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           id == rhs.id;
}

bool InvalidateAssetMetadata::operator!=(const InvalidateAssetMetadata& rhs) const {
    return !(rhs == *this);
}

}
