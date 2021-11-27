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

#include "enjinsdk/project/GetWallets.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

GetWallets::GetWallets() : graphql::AbstractGraphqlRequest("enjin.sdk.project.GetWallets") {
}

std::string GetWallets::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_objects_to_document(document, {
            WalletFragmentArguments::serialize(),
            PaginationArguments::serialize()
    });

    if (user_ids.has_value()) {
        utils::set_array_member_from_string_vector(document, "userIds", user_ids.value());
    }
    if (eth_addresses.has_value()) {
        utils::set_array_member_from_string_vector(document, "ethAddresses", eth_addresses.value());
    }

    return utils::document_to_string(document);
}

GetWallets& GetWallets::set_user_ids(std::vector<std::string> user_ids) {
    GetWallets::user_ids = std::move(user_ids);
    return *this;
}

GetWallets& GetWallets::set_eth_addresses(std::vector<std::string> eth_addresses) {
    GetWallets::eth_addresses = std::move(eth_addresses);
    return *this;
}

bool GetWallets::operator==(const GetWallets& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::WalletFragmentArguments<GetWallets>&>(*this) ==
           static_cast<const shared::WalletFragmentArguments<GetWallets>&>(rhs) &&
           static_cast<const shared::PaginationArguments<GetWallets>&>(*this) ==
           static_cast<const shared::PaginationArguments<GetWallets>&>(rhs) &&
           user_ids == rhs.user_ids &&
           eth_addresses == rhs.eth_addresses;
}

bool GetWallets::operator!=(const GetWallets& rhs) const {
    return !(rhs == *this);
}

}
