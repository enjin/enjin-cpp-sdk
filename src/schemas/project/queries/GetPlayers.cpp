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

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetPlayers::GetPlayers() : AbstractGraphqlRequest("enjin.sdk.project.GetPlayers"),
                           PlayerFragmentArguments<GetPlayers>(),
                           PaginationArguments<GetPlayers>() {
}

std::string GetPlayers::serialize() const {
    return to_json().to_string();
}

GetPlayers& GetPlayers::set_filter(PlayerFilter filter) {
    filter_opt = std::move(filter);
    return *this;
}

JsonValue GetPlayers::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, PlayerFragmentArguments<GetPlayers>::to_json());
    JsonUtils::join_object(json, PaginationArguments<GetPlayers>::to_json());
    JsonUtils::try_set_field(json, "filter", filter_opt);

    return json;
}

bool GetPlayers::operator==(const GetPlayers& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const PlayerFragmentArguments<GetPlayers>&>(*this) == rhs
           && static_cast<const PaginationArguments<GetPlayers>&>(*this) == rhs
           && filter_opt == rhs.filter_opt;
}

bool GetPlayers::operator!=(const GetPlayers& rhs) const {
    return !(*this == rhs);
}
