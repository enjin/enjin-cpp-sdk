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

#include "enjinsdk/player/BridgeAsset.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::player {

BridgeAsset::BridgeAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.player.BridgeAsset") {
}

std::string BridgeAsset::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionFragmentArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, "value", value.value());
    }

    return utils::document_to_string(document);
}

BridgeAsset& BridgeAsset::set_asset_id(std::string asset_id) {
    BridgeAsset::asset_id = asset_id;
    return *this;
}

BridgeAsset& BridgeAsset::set_asset_index(std::string asset_index) {
    BridgeAsset::asset_index = asset_index;
    return *this;
}

BridgeAsset& BridgeAsset::set_value(std::string value) {
    BridgeAsset::value = value;
    return *this;
}

bool BridgeAsset::operator==(const BridgeAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionFragmentArguments<BridgeAsset>&>(*this) ==
           static_cast<const TransactionFragmentArguments<BridgeAsset>&>(rhs) &&
            asset_id == rhs.asset_id &&
            asset_index == rhs.asset_index &&
            value == rhs.value;
}

bool BridgeAsset::operator!=(const BridgeAsset& rhs) const {
    return !(rhs == *this);
}

}
