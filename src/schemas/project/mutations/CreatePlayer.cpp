#include "enjinsdk/project/CreatePlayer.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

CreatePlayer::CreatePlayer() : graphql::AbstractGraphqlRequest("enjin.sdk.project.CreatePlayer") {
}

std::string CreatePlayer::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (id.has_value()) {
        utils::set_string_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

CreatePlayer& CreatePlayer::set_id(const std::string& id) {
    CreatePlayer::id = id;
    return *this;
}

bool CreatePlayer::operator==(const CreatePlayer& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           id == rhs.id;
}

bool CreatePlayer::operator!=(const CreatePlayer& rhs) const {
    return !(rhs == *this);
}

}
