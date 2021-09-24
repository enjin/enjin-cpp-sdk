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

#include "enjinsdk/project/AdvancedSendAsset.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

AdvancedSendAsset::AdvancedSendAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.project.AdvancedSendAsset") {
}

std::string AdvancedSendAsset::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (transfers.has_value()) {
        utils::set_array_member_from_type_vector<models::Transfer>(document, "transfers", transfers.value());
    }
    if (data.has_value()) {
        utils::set_string_member(document, "data", data.value());
    }

    return utils::document_to_string(document);
}

AdvancedSendAsset& AdvancedSendAsset::set_transfers(const std::vector<models::Transfer>& transfers) {
    AdvancedSendAsset::transfers = transfers;
    return *this;
}

AdvancedSendAsset& AdvancedSendAsset::set_data(const std::string& data) {
    AdvancedSendAsset::data = data;
    return *this;
}

bool AdvancedSendAsset::operator==(const AdvancedSendAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<AdvancedSendAsset>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<AdvancedSendAsset>&>(rhs) &&
           transfers == rhs.transfers &&
           data == rhs.data;
}

bool AdvancedSendAsset::operator!=(const AdvancedSendAsset& rhs) const {
    return !(rhs == *this);
}

}
