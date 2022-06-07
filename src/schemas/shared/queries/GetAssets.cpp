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

#include "enjinsdk/shared/GetAssets.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetAssets::GetAssets() : AbstractGraphqlRequest("enjin.sdk.shared.GetAssets"),
                         AssetFragmentArguments<GetAssets>(),
                         PaginationArguments<GetAssets>() {
}

std::string GetAssets::serialize() const {
    return to_json().to_string();
}

GetAssets& GetAssets::set_filter(models::AssetFilter filter) {
    filter_opt = std::move(filter);
    return *this;
}

GetAssets& GetAssets::set_sort(models::AssetSort sort) {
    sort_opt = std::move(sort);
    return *this;
}

JsonValue GetAssets::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, AssetFragmentArguments<GetAssets>::to_json());
    JsonUtils::join_object(json, PaginationArguments<GetAssets>::to_json());
    JsonUtils::try_set_field(json, "filter", filter_opt);
    JsonUtils::try_set_field(json, "sort", sort_opt);

    return json;
}

bool GetAssets::operator==(const GetAssets& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const AssetFragmentArguments<GetAssets>&>(*this) == rhs
           && static_cast<const PaginationArguments<GetAssets>&>(*this) == rhs
           && filter_opt == rhs.filter_opt
           && sort_opt == rhs.sort_opt;
}

bool GetAssets::operator!=(const GetAssets& rhs) const {
    return !(*this == rhs);
}
