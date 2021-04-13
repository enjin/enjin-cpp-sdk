#include "enjinsdk/shared/SendAsset.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

SendAsset::SendAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.SendAsset") {
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
           static_cast<const TransactionRequestArguments<SendAsset>&>(*this) ==
           static_cast<const TransactionRequestArguments<SendAsset>&>(rhs) &&
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
