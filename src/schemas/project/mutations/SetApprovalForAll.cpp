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

#include "enjinsdk/project/SetApprovalForAll.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

SetApprovalForAll::SetApprovalForAll() : AbstractGraphqlRequest("enjin.sdk.project.SetApprovalForAll"),
                                         ProjectTransactionRequestArguments<SetApprovalForAll>() {
}

std::string SetApprovalForAll::serialize() const {
    return to_json().to_string();
}

SetApprovalForAll& SetApprovalForAll::set_operator_address(std::string operator_address) {
    operator_address_opt = std::move(operator_address);
    return *this;
}

SetApprovalForAll& SetApprovalForAll::set_approved(bool approved) {
    approved_opt = approved;
    return *this;
}

JsonValue SetApprovalForAll::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<SetApprovalForAll>::to_json());
    JsonUtils::try_set_field(json, "operatorAddress", operator_address_opt);
    JsonUtils::try_set_field(json, "approved", approved_opt);

    return json;
}

bool SetApprovalForAll::operator==(const SetApprovalForAll& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<SetApprovalForAll>&>(*this) == rhs
           && operator_address_opt == rhs.operator_address_opt
           && approved_opt == rhs.approved_opt;
}

bool SetApprovalForAll::operator!=(const SetApprovalForAll& rhs) const {
    return !(*this == rhs);
}
