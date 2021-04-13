#include "enjinsdk/shared/GetProject.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetProject::GetProject() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetProject") {
}

std::string GetProject::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (id.has_value()) {
        utils::set_integer_member(document, "id", id.value());
    }
    if (name.has_value()) {
        utils::set_string_member(document, "name", name.value());
    }

    return utils::document_to_string(document);
}

GetProject& GetProject::set_id(int id) {
    GetProject::id = id;
    return *this;
}

GetProject& GetProject::set_name(const std::string& name) {
    GetProject::name = name;
    return *this;
}

bool GetProject::operator==(const GetProject& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           id == rhs.id &&
           name == rhs.name;
}

bool GetProject::operator!=(const GetProject& rhs) const {
    return !(rhs == *this);
}

}
