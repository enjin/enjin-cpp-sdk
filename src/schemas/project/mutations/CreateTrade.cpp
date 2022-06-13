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

#include "enjinsdk/project/CreateTrade.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

CreateTrade::CreateTrade() : AbstractGraphqlRequest("enjin.sdk.project.CreateTrade"),
                             ProjectTransactionRequestArguments<CreateTrade>() {
}

std::string CreateTrade::serialize() const {
    return to_json().to_string();
}

CreateTrade& CreateTrade::set_asking_assets(std::vector<Trade> assets) {
    asking_assets_opt = std::move(assets);
    return *this;
}

CreateTrade& CreateTrade::set_offering_assets(std::vector<Trade> assets) {
    offering_assets_opt = std::move(assets);
    return *this;
}

CreateTrade& CreateTrade::set_recipient_address(std::string recipient_address) {
    recipient_address_opt = std::move(recipient_address);
    return *this;
}

JsonValue CreateTrade::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<CreateTrade>::to_json());
    JsonUtils::try_set_field(json, "askingAssets", asking_assets_opt);
    JsonUtils::try_set_field(json, "offeringAssets", offering_assets_opt);
    JsonUtils::try_set_field(json, "recipientAddress", recipient_address_opt);

    return json;
}

bool CreateTrade::operator==(const CreateTrade& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<CreateTrade>&>(*this) == rhs
           && asking_assets_opt == rhs.asking_assets_opt
           && offering_assets_opt == rhs.offering_assets_opt
           && recipient_address_opt == rhs.recipient_address_opt;
}

bool CreateTrade::operator!=(const CreateTrade& rhs) const {
    return !(*this == rhs);
}
