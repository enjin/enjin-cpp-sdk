#include "enjinsdk/project/AuthPlayer.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

AuthPlayer::AuthPlayer() : graphql::AbstractGraphqlRequest("enjin.sdk.project.AuthPlayer") {
}

std::string AuthPlayer::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (id.has_value()) {
        utils::set_string_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

AuthPlayer& AuthPlayer::set_id(const std::string& id) {
    AuthPlayer::id = id;
    return *this;
}

bool AuthPlayer::operator==(const AuthPlayer& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           id == rhs.id;
}

bool AuthPlayer::operator!=(const AuthPlayer& rhs) const {
    return !(rhs == *this);
}

}
