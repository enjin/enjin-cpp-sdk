#include "enjinsdk/project/SetTransferFee.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetTransferFee::SetTransferFee() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetTransferFee") {
}

std::string SetTransferFee::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
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

SetTransferFee& SetTransferFee::set_asset_index(const std::string& asset_index) {
    SetTransferFee::asset_index = asset_index;
    return *this;
}

SetTransferFee& SetTransferFee::set_transfer_fee(const std::string& transfer_fee) {
    SetTransferFee::transfer_fee = transfer_fee;
    return *this;
}

bool SetTransferFee::operator==(const SetTransferFee& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetTransferFee>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetTransferFee>&>(rhs) &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           transfer_fee == rhs.transfer_fee;
}

bool SetTransferFee::operator!=(const SetTransferFee& rhs) const {
    return !(rhs == *this);
}

}
