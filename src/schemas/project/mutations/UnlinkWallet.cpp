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

#include "enjinsdk/project/UnlinkWallet.hpp"

#include "RapidJsonUtils.hpp"
#include <utility>

namespace enjin::sdk::project {

UnlinkWallet::UnlinkWallet() : graphql::AbstractGraphqlRequest("enjin.sdk.project.UnlinkWallet") {
}

std::string UnlinkWallet::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (eth_address.has_value()) {
        utils::set_string_member(document, "ethAddress", eth_address.value());
    }

    return utils::document_to_string(document);
}

UnlinkWallet& UnlinkWallet::set_eth_address(std::string eth_address) {
    UnlinkWallet::eth_address = std::move(eth_address);
    return *this;
}

bool UnlinkWallet::operator==(const UnlinkWallet& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           eth_address == rhs.eth_address;
}

bool UnlinkWallet::operator!=(const UnlinkWallet& rhs) const {
    return !(rhs == *this);
}

}
