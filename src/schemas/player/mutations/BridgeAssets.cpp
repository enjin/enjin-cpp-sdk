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

#include "enjinsdk/player/BridgeAssets.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::player;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

BridgeAssets::BridgeAssets() : AbstractGraphqlRequest("enjin.sdk.player.BridgeAssets"),
                               TransactionFragmentArguments<BridgeAssets>() {
}

std::string BridgeAssets::serialize() const {
    return to_json().to_string();
}

BridgeAssets& BridgeAssets::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

BridgeAssets& BridgeAssets::set_asset_indices(std::vector<std::string> asset_indices) {
    asset_indices_opt = std::move(asset_indices);
    return *this;
}

JsonValue BridgeAssets::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionFragmentArguments<BridgeAssets>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "assetIndices", asset_indices_opt);

    return json;
}

bool BridgeAssets::operator==(const BridgeAssets& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionFragmentArguments<BridgeAssets>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt
           && asset_indices_opt == rhs.asset_indices_opt;
}

bool BridgeAssets::operator!=(const BridgeAssets& rhs) const {
    return !(*this == rhs);
}
