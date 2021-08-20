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

#include "enjinsdk/project/CreateTrade.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

CreateTrade::CreateTrade() : graphql::AbstractGraphqlRequest("enjin.sdk.project.CreateTrade") {

}

std::string CreateTrade::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (asking_assets.has_value()) {
        utils::set_array_member_from_type_vector<models::Trade>(document, "askingAssets", asking_assets.value());
    }
    if (offering_assets.has_value()) {
        utils::set_array_member_from_type_vector<models::Trade>(document, "offeringAssets", offering_assets.value());
    }
    if (recipient_address.has_value()) {
        utils::set_string_member(document, "recipientAddress", recipient_address.value());
    }

    return utils::document_to_string(document);
}

CreateTrade& CreateTrade::set_asking_assets(std::vector<models::Trade> assets) {
    asking_assets = assets;
    return *this;
}

CreateTrade& CreateTrade::set_offering_assets(std::vector<models::Trade> assets) {
    offering_assets = assets;
    return *this;
}

CreateTrade& CreateTrade::set_recipient_address(const std::string& recipient_address) {
    CreateTrade::recipient_address = recipient_address;
    return *this;
}

bool CreateTrade::operator==(const CreateTrade& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<CreateTrade>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<CreateTrade>&>(rhs) &&
           asking_assets == rhs.asking_assets &&
           offering_assets == rhs.offering_assets &&
           recipient_address == rhs.recipient_address;
}

bool CreateTrade::operator!=(const CreateTrade& rhs) const {
    return !(rhs == *this);
}

}
