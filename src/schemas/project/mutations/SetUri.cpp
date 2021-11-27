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

#include "enjinsdk/project/SetUri.hpp"

#include "RapidJsonUtils.hpp"
#include <utility>

namespace enjin::sdk::project {

SetUri::SetUri() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetUri") {
}

std::string SetUri::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
    }
    if (uri.has_value()) {
        utils::set_string_member(document, "uri", uri.value());
    }

    return utils::document_to_string(document);
}

SetUri& SetUri::set_asset_id(std::string asset_id) {
    SetUri::asset_id = std::move(asset_id);
    return *this;
}

SetUri& SetUri::set_asset_index(std::string asset_index) {
    SetUri::asset_index = std::move(asset_index);
    return *this;
}

SetUri& SetUri::set_uri(std::string uri) {
    SetUri::uri = std::move(uri);
    return *this;
}

bool SetUri::operator==(const SetUri& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<SetUri>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<SetUri>&>(rhs) &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           uri == rhs.uri;
}

bool SetUri::operator!=(const SetUri& rhs) const {
    return !(rhs == *this);
}

}
