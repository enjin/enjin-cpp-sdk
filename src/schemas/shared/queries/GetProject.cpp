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

    return utils::document_to_string(document);
}

bool GetProject::operator==(const GetProject& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs);
}

bool GetProject::operator!=(const GetProject& rhs) const {
    return !(rhs == *this);
}

}
