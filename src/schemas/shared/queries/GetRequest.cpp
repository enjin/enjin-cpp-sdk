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

#include "RapidJsonUtils.hpp"
#include <utility>

namespace enjin::sdk::shared {

GetRequest::GetRequest() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetRequest") {
}

std::string GetRequest::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionFragmentArguments::serialize());

    if (id.has_value()) {
        utils::set_integer_member(document, "id", id.value());
    }
    if (transaction_id.has_value()) {
        utils::set_string_member(document, "transactionId", transaction_id.value());
    }

    return utils::document_to_string(document);
}

GetRequest& GetRequest::set_id(int id) {
    GetRequest::id = id;
    return *this;
}

GetRequest& GetRequest::set_transaction_id(std::string id) {
    transaction_id = std::move(id);
    return *this;
}

bool GetRequest::operator==(const GetRequest& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionFragmentArguments<GetRequest>&>(*this) ==
           static_cast<const TransactionFragmentArguments<GetRequest>&>(rhs) &&
           id == rhs.id &&
           transaction_id == rhs.transaction_id;
}

bool GetRequest::operator!=(const GetRequest& rhs) const {
    return !(rhs == *this);
}

}
