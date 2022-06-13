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

#include "enjinsdk/project/BridgeAsset.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

BridgeAsset::BridgeAsset() : AbstractGraphqlRequest("enjin.sdk.project.BridgeAsset"),
                             ProjectTransactionRequestArguments<BridgeAsset>() {
}

std::string BridgeAsset::serialize() const {
    return to_json().to_string();
}

BridgeAsset& BridgeAsset::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

BridgeAsset& BridgeAsset::set_asset_index(std::string asset_index) {
    asset_index_opt = std::move(asset_index);
    return *this;
}

BridgeAsset& BridgeAsset::set_value(std::string value) {
    value_opt = std::move(value);
    return *this;
}

JsonValue BridgeAsset::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<BridgeAsset>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "assetIndex", asset_index_opt);
    JsonUtils::try_set_field(json, "value", value_opt);

    return json;
}

bool BridgeAsset::operator==(const BridgeAsset& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<BridgeAsset>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt
           && asset_index_opt == rhs.asset_index_opt
           && value_opt == rhs.value_opt;
}

bool BridgeAsset::operator!=(const BridgeAsset& rhs) const {
    return !(*this == rhs);
}
