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

#include "enjinsdk/project/SetMeltFee.hpp"

#include "RapidJsonUtils.hpp"
#include <utility>

namespace enjin::sdk::project {

SetMeltFee::SetMeltFee() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetMeltFee") {
}

std::string SetMeltFee::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (melt_fee.has_value()) {
        utils::set_integer_member(document, "meltFee", melt_fee.value());
    }

    return utils::document_to_string(document);
}

SetMeltFee& SetMeltFee::set_asset_id(std::string asset_id) {
    SetMeltFee::asset_id = std::move(asset_id);
    return *this;
}

SetMeltFee& SetMeltFee::set_melt_fee(int melt_fee) {
    SetMeltFee::melt_fee = melt_fee;
    return *this;
}

bool SetMeltFee::operator==(const SetMeltFee& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<SetMeltFee>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<SetMeltFee>&>(rhs) &&
           asset_id == rhs.asset_id &&
           melt_fee == rhs.melt_fee;
}

bool SetMeltFee::operator!=(const SetMeltFee& rhs) const {
    return !(rhs == *this);
}

}
