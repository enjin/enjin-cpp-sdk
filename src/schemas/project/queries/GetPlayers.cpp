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

#include "enjinsdk/project/GetPlayers.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

GetPlayers::GetPlayers() : graphql::AbstractGraphqlRequest("enjin.sdk.project.GetPlayers") {
}

std::string GetPlayers::serialize() const {
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
