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

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

CompleteTrade::CompleteTrade() : graphql::AbstractGraphqlRequest("enjin.sdk.project.CompleteTrade") {
}

std::string CompleteTrade::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (trade_id.has_value()) {
        utils::set_string_member(document, "tradeId", trade_id.value());
    }

    return utils::document_to_string(document);
}

CompleteTrade& CompleteTrade::set_trade_id(const std::string& id) {
    trade_id = id;
    return *this;
}

bool CompleteTrade::operator==(const CompleteTrade& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<CompleteTrade>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<CompleteTrade>&>(rhs) &&
           trade_id == rhs.trade_id;
}

bool CompleteTrade::operator!=(const CompleteTrade& rhs) const {
    return !(rhs == *this);
}

}
