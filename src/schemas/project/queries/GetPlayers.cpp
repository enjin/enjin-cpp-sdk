#include "enjinsdk/project/GetPlayers.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

GetPlayers::GetPlayers() : graphql::AbstractGraphqlRequest("enjin.sdk.project.GetPlayers") {
}

std::string GetPlayers::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_objects_to_document(document, {
            PlayerFragmentArguments::serialize(),
            PaginationArguments::serialize()
    });

    if (filter.has_value()) {
        utils::set_object_member_from_type<models::PlayerFilter>(document, "filter", filter.value());
    }

    return utils::document_to_string(document);
}

GetPlayers& GetPlayers::set_filter(const models::PlayerFilter& filter) {
    GetPlayers::filter = filter;
    return *this;
}

bool GetPlayers::operator==(const GetPlayers& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::PlayerFragmentArguments<GetPlayers>&>(*this) ==
           static_cast<const shared::PlayerFragmentArguments<GetPlayers>&>(rhs) &&
           static_cast<const shared::PaginationArguments<GetPlayers>&>(*this) ==
           static_cast<const shared::PaginationArguments<GetPlayers>&>(rhs) &&
           filter == rhs.filter;
}

bool GetPlayers::operator!=(const GetPlayers& rhs) const {
    return !(rhs == *this);
}

}
