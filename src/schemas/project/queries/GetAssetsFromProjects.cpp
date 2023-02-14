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

#include "enjinsdk/project/GetAssetsFromProjects.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

GetAssetsFromProjects::GetAssetsFromProjects() : AbstractGraphqlRequest("enjin.sdk.project.GetAssetsFromProjects"),
                                                 AssetFragmentArguments<GetAssetsFromProjects>(),
                                                 PaginationArguments<GetAssetsFromProjects>() {
}

std::string GetAssetsFromProjects::serialize() const {
    return to_json().to_string();
}

GetAssetsFromProjects& GetAssetsFromProjects::set_projects(std::vector<std::string> projects) {
    projects_opt = std::move(projects);
    return *this;
}

GetAssetsFromProjects& GetAssetsFromProjects::set_filter(AssetFilter filter) {
    filter_opt = std::move(filter);
    return *this;
}

GetAssetsFromProjects& GetAssetsFromProjects::set_sort(AssetSortInput sort) {
    sort_opt = std::move(sort);
    return *this;
}

JsonValue GetAssetsFromProjects::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, AssetFragmentArguments<GetAssetsFromProjects>::to_json());
    JsonUtils::join_object(json, PaginationArguments<GetAssetsFromProjects>::to_json());
    JsonUtils::try_set_field(json, "projects", projects_opt);
    JsonUtils::try_set_field(json, "filter", filter_opt);
    JsonUtils::try_set_field(json, "sort", sort_opt);

    return json;
}

bool GetAssetsFromProjects::operator==(const GetAssetsFromProjects& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const AssetFragmentArguments <GetAssetsFromProjects>&>(*this) == rhs
           && static_cast<const PaginationArguments <GetAssetsFromProjects>&>(*this) == rhs
           && projects_opt == rhs.projects_opt
           && filter_opt == rhs.filter_opt
           && sort_opt == rhs.sort_opt;
}

bool GetAssetsFromProjects::operator!=(const GetAssetsFromProjects& rhs) const {
    return !(*this == rhs);
}
