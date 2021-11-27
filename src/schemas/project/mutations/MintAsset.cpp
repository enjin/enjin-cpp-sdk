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

#include "enjinsdk/project/MintAsset.hpp"

#include "RapidJsonUtils.hpp"
#include <utility>

namespace enjin::sdk::project {

MintAsset::MintAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.project.MintAsset") {
}

std::string MintAsset::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (mints.has_value()) {
        utils::set_array_member_from_type_vector<models::MintInput>(document, "mints", mints.value());
    }

    return utils::document_to_string(document);
}

MintAsset& MintAsset::set_asset_id(std::string asset_id) {
    MintAsset::asset_id = std::move(asset_id);
    return *this;
}

MintAsset& MintAsset::set_mints(std::vector<models::MintInput> mints) {
    MintAsset::mints = std::move(mints);
    return *this;
}

bool MintAsset::operator==(const MintAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<MintAsset>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<MintAsset>&>(rhs) &&
           asset_id == rhs.asset_id &&
           mints == rhs.mints;
}

bool MintAsset::operator!=(const MintAsset& rhs) const {
    return !(rhs == *this);
}

}
