/* Copyright 2021 Enjin Pte Ltd.
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

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetTransferable::SetTransferable() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetTransferable") {
}

std::string SetTransferable::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
    }
    if (transferable.has_value()) {
        utils::set_string_member(document, "transferable", utils::serialize_asset_transferable(transferable.value()));
    }

    return utils::document_to_string(document);
}

SetTransferable& SetTransferable::set_asset_id(const std::string& asset_id) {
    SetTransferable::asset_id = asset_id;
    return *this;
}

SetTransferable& SetTransferable::set_asset_index(const std::string& asset_index) {
    SetTransferable::asset_index = asset_index;
    return *this;
}

SetTransferable& SetTransferable::set_transferable(models::AssetTransferable transferable) {
    SetTransferable::transferable = transferable;
    return *this;
}

bool SetTransferable::operator==(const SetTransferable& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<SetTransferable>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<SetTransferable>&>(rhs) &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           transferable == rhs.transferable;
}

bool SetTransferable::operator!=(const SetTransferable& rhs) const {
    return !(rhs == *this);
}

}
