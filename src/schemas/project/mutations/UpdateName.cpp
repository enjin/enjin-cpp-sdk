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

#include "enjinsdk/project/UpdateName.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

UpdateName::UpdateName() : AbstractGraphqlRequest("enjin.sdk.project.UpdateName"),
                           TransactionRequestArguments<UpdateName>() {
}

std::string UpdateName::serialize() const {
    return TransactionRequestArguments::serialize();
}

UpdateName& UpdateName::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

UpdateName& UpdateName::set_name(std::string name) {
    name_opt = std::move(name);
    return *this;
}

JsonValue UpdateName::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionRequestArguments<UpdateName>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "name", name_opt);

    return json;
}

bool UpdateName::operator==(const UpdateName& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionRequestArguments<UpdateName>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt
           && name_opt == rhs.name_opt;
}

bool UpdateName::operator!=(const UpdateName& rhs) const {
    return !(*this == rhs);
}
