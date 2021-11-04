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

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

BridgeClaimAsset::BridgeClaimAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.project.BridgeClaimAsset") {
}

std::string BridgeClaimAsset::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }

    return utils::document_to_string(document);
}

BridgeClaimAsset& BridgeClaimAsset::set_asset_id(std::string asset_id) {
    BridgeClaimAsset::asset_id = asset_id;
    return *this;
}

bool BridgeClaimAsset::operator==(const BridgeClaimAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<BridgeClaimAsset>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<BridgeClaimAsset>&>(rhs) &&
           asset_id == rhs.asset_id;
}

bool BridgeClaimAsset::operator!=(const BridgeClaimAsset& rhs) const {
    return !(rhs == *this);
}

}
