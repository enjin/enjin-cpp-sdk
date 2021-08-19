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

#include "enjinsdk/player/SendAsset.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::player {

SendAsset::SendAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.player.SendAsset") {
}

std::string SendAsset::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (recipient_address.has_value()) {
        utils::set_string_member(document, "recipientAddress", recipient_address.value());
    }
    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, "value", value.value());
    }
    if (data.has_value()) {
        utils::set_string_member(document, "data", data.value());
    }

    return utils::document_to_string(document);
}

SendAsset& SendAsset::set_recipient_address(const std::string& recipient_address) {
    SendAsset::recipient_address = recipient_address;
    return *this;
}

SendAsset& SendAsset::set_asset_id(const std::string& asset_id) {
    SendAsset::asset_id = asset_id;
    return *this;
}

SendAsset& SendAsset::set_asset_index(const std::string& asset_index) {
    SendAsset::asset_index = asset_index;
    return *this;
}

SendAsset& SendAsset::set_value(const std::string& value) {
    SendAsset::value = value;
    return *this;
}

SendAsset& SendAsset::set_data(const std::string& data) {
    SendAsset::data = data;
    return *this;
}

bool SendAsset::operator==(const SendAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArguments<SendAsset>&>(*this) ==
           static_cast<const shared::TransactionRequestArguments<SendAsset>&>(rhs) &&
           recipient_address == rhs.recipient_address &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           value == rhs.value &&
           data == rhs.data;
}

bool SendAsset::operator!=(const SendAsset& rhs) const {
    return !(rhs == *this);
}

}
