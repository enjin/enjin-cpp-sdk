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

#include "RapidJsonUtils.hpp"
#include <utility>

namespace enjin::sdk::project {

BridgeAssets::BridgeAssets() : graphql::AbstractGraphqlRequest("enjin.sdk.project.BridgeAssets") {
}

std::string BridgeAssets::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_indices.has_value()) {
        utils::set_array_member_from_string_vector(document, "assetIndices", asset_indices.value());
    }

    return utils::document_to_string(document);
}

BridgeAssets& BridgeAssets::set_asset_id(std::string asset_id) {
    BridgeAssets::asset_id = std::move(asset_id);
    return *this;
}

BridgeAssets& BridgeAssets::set_asset_indices(std::vector<std::string> asset_indices) {
    BridgeAssets::asset_indices = std::move(asset_indices);
    return *this;
}

bool BridgeAssets::operator==(const BridgeAssets& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<BridgeAssets>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<BridgeAssets>&>(rhs) &&
           asset_id == rhs.asset_id &&
           asset_indices == rhs.asset_indices;
}

bool BridgeAssets::operator!=(const BridgeAssets& rhs) const {
    return !(rhs == *this);
}

}
