#include "enjinsdk/project/GetPlayer.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

enjin::sdk::project::GetPlayer::GetPlayer() : graphql::AbstractGraphqlRequest("enjin.sdk.project.GetPlayer") {
}

std::string GetPlayer::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, PlayerFragmentArguments::serialize());

    if (id.has_value()) {
        utils::set_string_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

GetPlayer& GetPlayer::set_id(const std::string& id) {
    GetPlayer::id = id;
    return *this;
}

bool GetPlayer::operator==(const GetPlayer& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::PlayerFragmentArguments<GetPlayer>&>(*this) ==
           static_cast<const shared::PlayerFragmentArguments<GetPlayer>&>(rhs) &&
           id == rhs.id;
}

bool GetPlayer::operator!=(const GetPlayer& rhs) const {
    return !(rhs == *this);
}

}
