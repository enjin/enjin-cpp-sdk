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

#include "enjinsdk/project/BridgeClaimAsset.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

BridgeClaimAsset::BridgeClaimAsset() : AbstractGraphqlRequest("enjin.sdk.project.BridgeClaimAsset"),
                                       ProjectTransactionRequestArguments<BridgeClaimAsset>() {
}

std::string BridgeClaimAsset::serialize() const {
    return to_json().to_string();
}

BridgeClaimAsset& BridgeClaimAsset::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

JsonValue BridgeClaimAsset::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<BridgeClaimAsset>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);

    return json;
}

bool BridgeClaimAsset::operator==(const BridgeClaimAsset& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<BridgeClaimAsset>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt;
}

bool BridgeClaimAsset::operator!=(const BridgeClaimAsset& rhs) const {
    return !(*this == rhs);
}
