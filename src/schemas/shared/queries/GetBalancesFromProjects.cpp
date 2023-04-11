/* Copyright 2023 Enjin Pte. Ltd.
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

#include "enjinsdk/shared/GetBalancesFromProjects.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetBalancesFromProjects::GetBalancesFromProjects() : AbstractGraphqlRequest("enjin.sdk.shared.GetBalancesFromProjects"),
                                                     BalanceFragmentArguments<GetBalancesFromProjects>(),
                                                     PaginationArguments<GetBalancesFromProjects>() {
}

std::string GetBalancesFromProjects::serialize() const {
    return to_json().to_string();
}

GetBalancesFromProjects& GetBalancesFromProjects::set_projects(std::vector<std::string> projects) {
    projects_opt = std::move(projects);
    return *this;
}

GetBalancesFromProjects& GetBalancesFromProjects::set_filter(BalanceFilter filter) {
    filter_opt = std::move(filter);
    return *this;
}

JsonValue GetBalancesFromProjects::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, BalanceFragmentArguments<GetBalancesFromProjects>::to_json());
    JsonUtils::join_object(json, PaginationArguments<GetBalancesFromProjects>::to_json());
    JsonUtils::try_set_field(json, "projects", projects_opt);
    JsonUtils::try_set_field(json, "filter", filter_opt);

    return json;
}

bool GetBalancesFromProjects::operator==(const GetBalancesFromProjects& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const BalanceFragmentArguments<GetBalancesFromProjects>&>(*this) == rhs
           && static_cast<const PaginationArguments<GetBalancesFromProjects>&>(*this) == rhs
           && projects_opt == rhs.projects_opt
           && filter_opt == rhs.filter_opt;
}

bool GetBalancesFromProjects::operator!=(const GetBalancesFromProjects& rhs) const {
    return !(*this == rhs);
}
