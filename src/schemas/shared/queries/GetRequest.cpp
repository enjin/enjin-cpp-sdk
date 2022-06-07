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

#include "enjinsdk/shared/GetRequest.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetRequest::GetRequest() : AbstractGraphqlRequest("enjin.sdk.shared.GetRequest"),
                           TransactionFragmentArguments<GetRequest>() {
}

std::string GetRequest::serialize() const {
    return to_json().to_string();
}

GetRequest& GetRequest::set_id(int id) {
    id_opt = id;
    return *this;
}

GetRequest& GetRequest::set_transaction_id(std::string id) {
    transaction_id_opt = std::move(id);
    return *this;
}

JsonValue GetRequest::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionFragmentArguments<GetRequest>::to_json());
    JsonUtils::try_set_field(json, "id", id_opt);
    JsonUtils::try_set_field(json, "transactionId", transaction_id_opt);

    return json;
}

bool GetRequest::operator==(const GetRequest& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionFragmentArguments<GetRequest>&>(*this) == rhs
           && id_opt == rhs.id_opt
           && transaction_id_opt == rhs.transaction_id_opt;
}

bool GetRequest::operator!=(const GetRequest& rhs) const {
    return !(*this == rhs);
}
