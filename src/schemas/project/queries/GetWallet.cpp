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

#include "enjinsdk/project/GetWallet.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetWallet::GetWallet() : AbstractGraphqlRequest("enjin.sdk.project.GetWallet"),
                         WalletFragmentArguments<GetWallet>() {
}

std::string GetWallet::serialize() const {
    return to_json().to_string();
}

GetWallet& GetWallet::set_user_id(std::string user_id) {
    user_id_opt = std::move(user_id);
    return *this;
}

GetWallet& GetWallet::set_eth_address(std::string eth_address) {
    eth_address_opt = std::move(eth_address);
    return *this;
}

JsonValue GetWallet::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, WalletFragmentArguments<GetWallet>::to_json());
    JsonUtils::try_set_field(json, "userId", user_id_opt);
    JsonUtils::try_set_field(json, "ethAddress", eth_address_opt);

    return json;
}

bool GetWallet::operator==(const GetWallet& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const WalletFragmentArguments<GetWallet>&>(*this) == rhs
           && user_id_opt == rhs.user_id_opt
           && eth_address_opt == rhs.eth_address_opt;
}

bool GetWallet::operator!=(const GetWallet& rhs) const {
    return !(*this == rhs);
}
