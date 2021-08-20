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

#include "enjinsdk/player/ApproveEnj.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::player {

ApproveEnj::ApproveEnj() : graphql::AbstractGraphqlRequest("enjin.sdk.player.ApproveEnj") {
}

std::string ApproveEnj::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionFragmentArguments::serialize());

    if (value.has_value()) {
        utils::set_string_member(document, "value", value.value());
    }

    return utils::document_to_string(document);
}

ApproveEnj& ApproveEnj::set_value(const std::string& value) {
    ApproveEnj::value = value;
    return *this;
}

bool ApproveEnj::operator==(const ApproveEnj& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionFragmentArguments<ApproveEnj>&>(*this) ==
           static_cast<const shared::TransactionFragmentArguments<ApproveEnj>&>(rhs) &&
           value == rhs.value;
}

bool ApproveEnj::operator!=(const ApproveEnj& rhs) const {
    return !(rhs == *this);
}

}
