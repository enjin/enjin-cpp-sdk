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

#include "enjinsdk/project/ReleaseReserve.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

ReleaseReserve::ReleaseReserve() : graphql::AbstractGraphqlRequest("enjin.sdk.project.ReleaseReserve") {
}

std::string ReleaseReserve::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, "value", value.value());
    }

    return utils::document_to_string(document);
}

ReleaseReserve& ReleaseReserve::set_asset_id(const std::string& asset_id) {
    ReleaseReserve::asset_id = asset_id;
    return *this;
}

ReleaseReserve& ReleaseReserve::set_value(const std::string& value) {
    ReleaseReserve::value = value;
    return *this;
}

bool ReleaseReserve::operator==(const ReleaseReserve& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<ReleaseReserve>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<ReleaseReserve>&>(rhs) &&
           asset_id == rhs.asset_id &&
           value == rhs.value;
}

bool ReleaseReserve::operator!=(const ReleaseReserve& rhs) const {
    return !(rhs == *this);
}

}
