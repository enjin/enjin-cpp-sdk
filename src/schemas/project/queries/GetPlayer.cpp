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

#include "enjinsdk/project/GetPlayer.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

enjin::sdk::project::GetPlayer::GetPlayer() : graphql::AbstractGraphqlRequest("enjin.sdk.project.GetPlayer") {
}

std::string GetPlayer::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, PlayerFragmentArguments::serialize());

    if (id.has_value()) {
        utils::set_string_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

GetPlayer& GetPlayer::set_id(std::string id) {
    GetPlayer::id = std::move(id);
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
