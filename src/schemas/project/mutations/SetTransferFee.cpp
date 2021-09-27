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

#include "enjinsdk/project/SetTransferFee.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetTransferFee::SetTransferFee() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetTransferFee") {
}

std::string SetTransferFee::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (transfer_fee.has_value()) {
        utils::set_string_member(document, "transferFee", transfer_fee.value());
    }

    return utils::document_to_string(document);
}

SetTransferFee& SetTransferFee::set_asset_id(const std::string& asset_id) {
    SetTransferFee::asset_id = asset_id;
    return *this;
}

SetTransferFee& SetTransferFee::set_transfer_fee(const std::string& transfer_fee) {
    SetTransferFee::transfer_fee = transfer_fee;
    return *this;
}

bool SetTransferFee::operator==(const SetTransferFee& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<SetTransferFee>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<SetTransferFee>&>(rhs) &&
           asset_id == rhs.asset_id &&
           transfer_fee == rhs.transfer_fee;
}

bool SetTransferFee::operator!=(const SetTransferFee& rhs) const {
    return !(rhs == *this);
}

}
