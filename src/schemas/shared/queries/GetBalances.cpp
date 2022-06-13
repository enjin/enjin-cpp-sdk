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

#include "enjinsdk/shared/GetBalances.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetBalances::GetBalances() : AbstractGraphqlRequest("enjin.sdk.shared.GetBalances"),
                             BalanceFragmentArguments<GetBalances>(),
                             PaginationArguments<GetBalances>() {
}

std::string GetBalances::serialize() const {
    return to_json().to_string();
}

GetBalances& GetBalances::set_filter(BalanceFilter filter) {
    filter_opt = std::move(filter);
    return *this;
}

JsonValue GetBalances::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, BalanceFragmentArguments<GetBalances>::to_json());
    JsonUtils::join_object(json, PaginationArguments<GetBalances>::to_json());
    JsonUtils::try_set_field(json, "filter", filter_opt);

    return json;
}

bool GetBalances::operator==(const GetBalances& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const BalanceFragmentArguments<GetBalances>&>(*this) == rhs
           && static_cast<const PaginationArguments<GetBalances>&>(*this) == rhs
           && filter_opt == rhs.filter_opt;
}

bool GetBalances::operator!=(const GetBalances& rhs) const {
    return !(*this == rhs);
}
