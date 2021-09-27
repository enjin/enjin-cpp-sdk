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

#include "enjinsdk/player/SendEnj.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::player {

SendEnj::SendEnj() : graphql::AbstractGraphqlRequest("enjin.sdk.player.SendEnj") {
}

std::string SendEnj::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionFragmentArguments::serialize());

    if (recipient_address.has_value()) {
        utils::set_string_member(document, "recipientAddress", recipient_address.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, "value", value.value());
    }

    return utils::document_to_string(document);
}

SendEnj& SendEnj::set_recipient_address(const std::string& recipient_address) {
    SendEnj::recipient_address = recipient_address;
    return *this;
}

SendEnj& SendEnj::set_value(const std::string& value) {
    SendEnj::value = value;
    return *this;
}

bool SendEnj::operator==(const SendEnj& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionFragmentArguments<SendEnj>&>(*this) ==
           static_cast<const shared::TransactionFragmentArguments<SendEnj>&>(rhs) &&
           recipient_address == rhs.recipient_address &&
           value == rhs.value;
}

bool SendEnj::operator!=(const SendEnj& rhs) const {
    return !(rhs == *this);
}

}
