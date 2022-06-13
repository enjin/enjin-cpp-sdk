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

#include "enjinsdk/project/SetTransferable.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

SetTransferable::SetTransferable() : AbstractGraphqlRequest("enjin.sdk.project.SetTransferable"),
                                     TransactionRequestArguments<SetTransferable>() {
}

std::string SetTransferable::serialize() const {
    return to_json().to_string();
}

SetTransferable& SetTransferable::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

SetTransferable& SetTransferable::set_asset_index(std::string asset_index) {
    asset_index_opt = std::move(asset_index);
    return *this;
}

SetTransferable& SetTransferable::set_transferable(AssetTransferable transferable) {
    transferable_opt = transferable;
    return *this;
}

JsonValue SetTransferable::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionRequestArguments<SetTransferable>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "assetIndex", asset_index_opt);
    JsonUtils::try_set_field(json, "transferable", transferable_opt);

    return json;
}

bool SetTransferable::operator==(const SetTransferable& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionRequestArguments<SetTransferable>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt
           && asset_index_opt == rhs.asset_index_opt
           && transferable_opt == rhs.transferable_opt;
}

bool SetTransferable::operator!=(const SetTransferable& rhs) const {
    return !(*this == rhs);
}
