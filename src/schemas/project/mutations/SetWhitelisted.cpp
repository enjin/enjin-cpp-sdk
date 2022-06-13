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

#include "enjinsdk/project/SetWhitelisted.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

SetWhitelisted::SetWhitelisted() : AbstractGraphqlRequest("enjin.sdk.project.SetWhitelisted"),
                                   ProjectTransactionRequestArguments<SetWhitelisted>() {
}

std::string SetWhitelisted::serialize() const {
    return to_json().to_string();
}

SetWhitelisted& SetWhitelisted::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

SetWhitelisted& SetWhitelisted::set_account_address(std::string account_address) {
    account_address_opt = std::move(account_address);
    return *this;
}

SetWhitelisted& SetWhitelisted::set_whitelisted(Whitelisted whitelisted) {
    whitelisted_opt = whitelisted;
    return *this;
}

SetWhitelisted& SetWhitelisted::set_whitelisted_address(std::string whitelisted_address) {
    whitelisted_address_opt = std::move(whitelisted_address);
    return *this;
}

SetWhitelisted& SetWhitelisted::set_on(bool on) {
    on_opt = on;
    return *this;
}

JsonValue SetWhitelisted::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<SetWhitelisted>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "accountAddress", account_address_opt);
    JsonUtils::try_set_field(json, "whitelisted", whitelisted_opt);
    JsonUtils::try_set_field(json, "whitelistedAddress", whitelisted_address_opt);
    JsonUtils::try_set_field(json, "on", on_opt);

    return json;
}

bool SetWhitelisted::operator==(const SetWhitelisted& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<SetWhitelisted>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt
           && account_address_opt == rhs.account_address_opt
           && whitelisted_opt == rhs.whitelisted_opt
           && whitelisted_address_opt == rhs.whitelisted_address_opt
           && on_opt == rhs.on_opt;
}

bool SetWhitelisted::operator!=(const SetWhitelisted& rhs) const {
    return !(*this == rhs);
}
