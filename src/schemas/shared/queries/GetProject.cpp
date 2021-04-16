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
