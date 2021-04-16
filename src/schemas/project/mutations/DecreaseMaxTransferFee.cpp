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

#include "enjinsdk/project/DecreaseMaxTransferFee.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

DecreaseMaxTransferFee::DecreaseMaxTransferFee()
        : graphql::AbstractGraphqlRequest("enjin.sdk.project.DecreaseMaxTransferFee") {
}

std::string DecreaseMaxTransferFee::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
    }
    if (max_transfer_fee.has_value()) {
        utils::set_integer_member(document, "maxTransferFee", max_transfer_fee.value());
    }

    return utils::document_to_string(document);
}

DecreaseMaxTransferFee& DecreaseMaxTransferFee::set_asset_id(const std::string& asset_id) {
    DecreaseMaxTransferFee::asset_id = asset_id;
    return *this;
}

DecreaseMaxTransferFee& DecreaseMaxTransferFee::set_asset_index(const std::string& asset_index) {
    DecreaseMaxTransferFee::asset_index = asset_index;
    return *this;
}

DecreaseMaxTransferFee& DecreaseMaxTransferFee::set_max_transfer_fee(int max_transfer_fee) {
    DecreaseMaxTransferFee::max_transfer_fee = max_transfer_fee;
    return *this;
}

bool DecreaseMaxTransferFee::operator==(const DecreaseMaxTransferFee& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArguments<DecreaseMaxTransferFee>&>(*this) ==
           static_cast<const shared::TransactionRequestArguments<DecreaseMaxTransferFee>&>(rhs) &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           max_transfer_fee == rhs.max_transfer_fee;
}

bool DecreaseMaxTransferFee::operator!=(const DecreaseMaxTransferFee& rhs) const {
    return !(rhs == *this);
}

}
