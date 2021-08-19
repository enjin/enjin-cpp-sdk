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

#include "enjinsdk/internal/TransactionRequestArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string TransactionRequestArgumentsImpl::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionFragmentArgumentsImpl::serialize());

    if (send.has_value()) {
        utils::set_boolean_member(document, "send", send.value());
    }

    return utils::document_to_string(document);
}

void TransactionRequestArgumentsImpl::set_send(bool send) {
    TransactionRequestArgumentsImpl::send = send;
}

bool TransactionRequestArgumentsImpl::operator==(const TransactionRequestArgumentsImpl& rhs) const {
    return static_cast<const TransactionFragmentArgumentsImpl&>(*this) ==
           static_cast<const TransactionFragmentArgumentsImpl&>(rhs) &&
           send == rhs.send;
}

bool TransactionRequestArgumentsImpl::operator!=(const TransactionRequestArgumentsImpl& rhs) const {
    return !(rhs == *this);
}

}
