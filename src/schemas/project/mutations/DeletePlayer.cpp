#include "enjinsdk/project/DeletePlayer.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

DeletePlayer::DeletePlayer() : graphql::AbstractGraphqlRequest("enjin.sdk.project.DeletePlayer") {
}

std::string DeletePlayer::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (id.has_value()) {
        utils::set_string_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

DeletePlayer& DeletePlayer::set_id(const std::string& id) {
    DeletePlayer::id = id;
    return *this;
}

bool DeletePlayer::operator==(const DeletePlayer& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           id == rhs.id;
}

bool DeletePlayer::operator!=(const DeletePlayer& rhs) const {
    return !(rhs == *this);
}

}
