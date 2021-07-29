/* Copyright 2021 Enjin Pte Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "enjinsdk/project/AuthProject.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

AuthProject::AuthProject() : graphql::AbstractGraphqlRequest("enjin.sdk.project.AuthProject") {
}

std::string AuthProject::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (uuid.has_value()) {
        utils::set_string_member(document, "uuid", uuid.value());
    }
    if (secret.has_value()) {
        utils::set_string_member(document, "secret", secret.value());
    }

    return utils::document_to_string(document);
}

AuthProject& AuthProject::set_uuid(const std::string& uuid) {
    AuthProject::uuid = uuid;
    return *this;
}

AuthProject& AuthProject::set_secret(const std::string& secret) {
    AuthProject::secret = secret;
    return *this;
}

bool AuthProject::operator==(const AuthProject& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           uuid == rhs.uuid &&
           secret == rhs.secret;
}

bool AuthProject::operator!=(const AuthProject& rhs) const {
    return !(rhs == *this);
}

}
