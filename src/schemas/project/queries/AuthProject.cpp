/* Copyright 2021 Enjin Pte. Ltd.
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

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

AuthProject::AuthProject() : AbstractGraphqlRequest("enjin.sdk.project.AuthProject") {
}

std::string AuthProject::serialize() const {
    return to_json().to_string();
}

AuthProject& AuthProject::set_uuid(std::string uuid) {
    uuid_opt = std::move(uuid);
    return *this;
}

AuthProject& AuthProject::set_secret(std::string secret) {
    secret_opt = std::move(secret);
    return *this;
}

JsonValue AuthProject::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::try_set_field(json, "uuid", uuid_opt);
    JsonUtils::try_set_field(json, "secret", secret_opt);

    return json;
}

bool AuthProject::operator==(const AuthProject& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && uuid_opt == rhs.uuid_opt
           && secret_opt == rhs.secret_opt;
}

bool AuthProject::operator!=(const AuthProject& rhs) const {
    return !(*this == rhs);
}
