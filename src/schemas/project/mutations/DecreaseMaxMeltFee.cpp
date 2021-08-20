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

#include "enjinsdk/project/DecreaseMaxMeltFee.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

DecreaseMaxMeltFee::DecreaseMaxMeltFee() : graphql::AbstractGraphqlRequest("enjin.sdk.project.DecreaseMaxMeltFee") {
}

std::string DecreaseMaxMeltFee::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (max_melt_fee.has_value()) {
        utils::set_integer_member(document, "maxMeltFee", max_melt_fee.value());
    }

    return utils::document_to_string(document);
}

DecreaseMaxMeltFee& DecreaseMaxMeltFee::set_asset_id(const std::string& asset_id) {
    DecreaseMaxMeltFee::asset_id = asset_id;
    return *this;
}

DecreaseMaxMeltFee& DecreaseMaxMeltFee::set_max_melt_fee(int max_melt_fee) {
    DecreaseMaxMeltFee::max_melt_fee = max_melt_fee;
    return *this;
}

bool DecreaseMaxMeltFee::operator==(const DecreaseMaxMeltFee& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<DecreaseMaxMeltFee>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<DecreaseMaxMeltFee>&>(rhs) &&
           asset_id == rhs.asset_id &&
           max_melt_fee == rhs.max_melt_fee;
}

bool DecreaseMaxMeltFee::operator!=(const DecreaseMaxMeltFee& rhs) const {
    return !(rhs == *this);
}

}
