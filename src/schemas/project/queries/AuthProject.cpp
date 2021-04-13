#include "enjinsdk/project/AuthProject.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

AuthProject::AuthProject() : graphql::AbstractGraphqlRequest("enjin.sdk.project.AuthProject") {
}

std::string AuthProject::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (id.has_value()) {
        utils::set_integer_member(document, "id", id.value());
    }
    if (secret.has_value()) {
        utils::set_string_member(document, "secret", secret.value());
    }

    return utils::document_to_string(document);
}

AuthProject& AuthProject::set_id(int id) {
    AuthProject::id = id;
    return *this;
}

AuthProject& AuthProject::set_secret(const std::string& secret) {
    AuthProject::secret = secret;
    return *this;
}

bool AuthProject::operator==(const AuthProject& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           id == rhs.id &&
           secret == rhs.secret;
}

bool AuthProject::operator!=(const AuthProject& rhs) const {
    return !(rhs == *this);
}

}
