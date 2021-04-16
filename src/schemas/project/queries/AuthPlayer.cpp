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
