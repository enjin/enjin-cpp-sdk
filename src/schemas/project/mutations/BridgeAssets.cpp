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

#include "enjinsdk/project/BridgeAssets.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

BridgeAssets::BridgeAssets() : AbstractGraphqlRequest("enjin.sdk.project.BridgeAssets"),
                               ProjectTransactionRequestArguments<BridgeAssets>() {
}

std::string BridgeAssets::serialize() const {
    return to_json().to_string();
}

BridgeAssets& BridgeAssets::set_asset_id(std::string asset_id) {
    BridgeAssets::asset_id = std::move(asset_id);
    return *this;
}

BridgeAssets& BridgeAssets::set_asset_indices(std::vector<std::string> asset_indices) {
    BridgeAssets::asset_indices = std::move(asset_indices);
    return *this;
}

JsonValue BridgeAssets::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<BridgeAssets>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id);
    JsonUtils::try_set_field(json, "assetIndices", asset_indices);

    return json;
}

bool BridgeAssets::operator==(const BridgeAssets& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<BridgeAssets>&>(*this) == rhs
           && asset_id == rhs.asset_id
           && asset_indices == rhs.asset_indices;
}

bool BridgeAssets::operator!=(const BridgeAssets& rhs) const {
    return !(*this == rhs);
}
