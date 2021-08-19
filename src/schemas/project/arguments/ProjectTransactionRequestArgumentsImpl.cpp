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

#include "enjinsdk/internal/ProjectTransactionRequestArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

std::string ProjectTransactionRequestArgumentsImpl::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, shared::TransactionRequestArgumentsImpl::serialize());

    if (eth_address.has_value()) {
        utils::set_string_member(document, "ethAddress", eth_address.value());
    }

    return utils::document_to_string(document);
}

void ProjectTransactionRequestArgumentsImpl::set_eth_address(const std::string& address) {
    ProjectTransactionRequestArgumentsImpl::eth_address = address;
}

bool ProjectTransactionRequestArgumentsImpl::operator==(const ProjectTransactionRequestArgumentsImpl& rhs) const {
    return static_cast<const TransactionRequestArgumentsImpl&>(*this) ==
           static_cast<const TransactionRequestArgumentsImpl&>(rhs) &&
           eth_address == rhs.eth_address;
}

bool ProjectTransactionRequestArgumentsImpl::operator!=(const ProjectTransactionRequestArgumentsImpl& rhs) const {
    return !(rhs == *this);
}

}
