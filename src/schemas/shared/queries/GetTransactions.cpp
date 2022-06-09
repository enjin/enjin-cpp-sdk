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

#include "enjinsdk/shared/GetTransactions.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetTransactions::GetTransactions() : AbstractGraphqlRequest("enjin.sdk.shared.GetTransactions") {
}

std::string GetTransactions::serialize() const {
    return to_json().to_string();
}

GetTransactions& GetTransactions::set_filter(TransactionFilter filter) {
    filter_opt = std::move(filter);
    return *this;
}

GetTransactions& GetTransactions::set_sort(TransactionSortInput sort) {
    sort_opt = std::move(sort);
    return *this;
}

JsonValue GetTransactions::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionFragmentArguments<GetTransactions>::to_json());
    JsonUtils::join_object(json, PaginationArguments<GetTransactions>::to_json());
    JsonUtils::try_set_field(json, "filter", filter_opt);
    JsonUtils::try_set_field(json, "sort", sort_opt);

    return json;
}

bool GetTransactions::operator==(const GetTransactions& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionFragmentArguments<GetTransactions>&>(*this) == rhs
           && static_cast<const PaginationArguments<GetTransactions>&>(*this) == rhs
           && filter_opt == rhs.filter_opt
           && sort_opt == rhs.sort_opt;
}

bool GetTransactions::operator!=(const GetTransactions& rhs) const {
    return !(*this == rhs);
}
