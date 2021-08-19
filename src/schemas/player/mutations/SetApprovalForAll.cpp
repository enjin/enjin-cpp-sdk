/* Copyright 2021 Enjin Pte Ltd.
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

#include "enjinsdk/player/SetApprovalForAll.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::player {

SetApprovalForAll::SetApprovalForAll() : graphql::AbstractGraphqlRequest("enjin.sdk.player.SetApprovalForAll") {
}

std::string SetApprovalForAll::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (operator_address.has_value()) {
        utils::set_string_member(document, "operatorAddress", operator_address.value());
    }
    if (approved.has_value()) {
        utils::set_boolean_member(document, "approved", approved.value());
    }

    return utils::document_to_string(document);
}

SetApprovalForAll& SetApprovalForAll::set_operator_address(const std::string& operator_address) {
    SetApprovalForAll::operator_address = operator_address;
    return *this;
}

SetApprovalForAll& SetApprovalForAll::set_approved(bool approved) {
    SetApprovalForAll::approved = approved;
    return *this;
}

bool SetApprovalForAll::operator==(const SetApprovalForAll& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArguments<SetApprovalForAll>&>(*this) ==
           static_cast<const shared::TransactionRequestArguments<SetApprovalForAll>&>(rhs) &&
           operator_address == rhs.operator_address &&
           approved == rhs.approved;
}

bool SetApprovalForAll::operator!=(const SetApprovalForAll& rhs) const {
    return !(rhs == *this);
}

}
