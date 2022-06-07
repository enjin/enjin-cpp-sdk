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

#include "enjinsdk/project/CompleteTrade.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

CompleteTrade::CompleteTrade() : AbstractGraphqlRequest("enjin.sdk.project.CompleteTrade"),
                                 ProjectTransactionRequestArguments<CompleteTrade>() {
}

std::string CompleteTrade::serialize() const {
    return to_json().to_string();
}

CompleteTrade& CompleteTrade::set_trade_id(std::string id) {
    trade_id_opt = std::move(id);
    return *this;
}

JsonValue CompleteTrade::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<CompleteTrade>::to_json());
    JsonUtils::try_set_field(json, "tradeId", trade_id_opt);

    return json;
}

bool CompleteTrade::operator==(const CompleteTrade& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<CompleteTrade>&>(*this) == rhs
           && trade_id_opt == rhs.trade_id_opt;
}

bool CompleteTrade::operator!=(const CompleteTrade& rhs) const {
    return !(*this == rhs);
}
