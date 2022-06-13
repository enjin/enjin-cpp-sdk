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

#include "enjinsdk/shared/GetRequests.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetRequests::GetRequests() : AbstractGraphqlRequest("enjin.sdk.shared.GetRequests") {
}

std::string GetRequests::serialize() const {
    return to_json().to_string();
}

GetRequests& GetRequests::set_filter(TransactionFilter filter) {
    filter_opt = std::move(filter);
    return *this;
}

GetRequests& GetRequests::set_sort(TransactionSort sort) {
    sort_opt = std::move(sort);
    return *this;
}

JsonValue GetRequests::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionFragmentArguments<GetRequests>::to_json());
    JsonUtils::join_object(json, PaginationArguments<GetRequests>::to_json());
    JsonUtils::try_set_field(json, "filter", filter_opt);
    JsonUtils::try_set_field(json, "sort", sort_opt);

    return json;
}

bool GetRequests::operator==(const GetRequests& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionFragmentArguments<GetRequests>&>(*this) == rhs
           && static_cast<const PaginationArguments<GetRequests>&>(*this) == rhs
           && filter_opt == rhs.filter_opt
           && sort_opt == rhs.sort_opt;
}

bool GetRequests::operator!=(const GetRequests& rhs) const {
    return !(*this == rhs);
}
