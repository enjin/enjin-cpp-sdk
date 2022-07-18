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

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetWallets::GetWallets() : AbstractGraphqlRequest("enjin.sdk.project.GetWallets"),
                           WalletFragmentArguments<GetWallets>() {
}

std::string GetWallets::serialize() const {
    return to_json().to_string();
}

GetWallets& GetWallets::set_user_ids(std::vector<std::string> user_ids) {
    user_ids_opt = std::move(user_ids);
    return *this;
}

GetWallets& GetWallets::set_eth_addresses(std::vector<std::string> eth_addresses) {
    eth_addresses_opt = std::move(eth_addresses);
    return *this;
}

JsonValue GetWallets::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, WalletFragmentArguments<GetWallets>::to_json());
    JsonUtils::try_set_field(json, "userIds", user_ids_opt);
    JsonUtils::try_set_field(json, "ethAddresses", eth_addresses_opt);

    return json;
}

bool GetWallets::operator==(const GetWallets& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const WalletFragmentArguments<GetWallets>&>(*this) == rhs
           && user_ids_opt == rhs.user_ids_opt
           && eth_addresses_opt == rhs.eth_addresses_opt;
}

bool GetWallets::operator!=(const GetWallets& rhs) const {
    return !(*this == rhs);
}
