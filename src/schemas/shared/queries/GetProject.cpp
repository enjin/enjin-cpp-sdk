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

#include "enjinsdk/shared/GetProject.hpp"

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::shared;

GetProject::GetProject() : AbstractGraphqlRequest("enjin.sdk.shared.GetProject") {
}

std::string GetProject::serialize() const {
    return to_json().to_string();
}

JsonValue GetProject::to_json() const {
    return JsonValue::create_object();
}

bool GetProject::operator==(const GetProject& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs;
}

bool GetProject::operator!=(const GetProject& rhs) const {
    return !(*this == rhs);
}
