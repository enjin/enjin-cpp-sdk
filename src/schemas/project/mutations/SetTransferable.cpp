#include "enjinsdk/project/SetTransferable.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetTransferable::SetTransferable() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetTransferable") {
}

std::string SetTransferable::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
    }
    if (transferable.has_value()) {
        utils::set_string_member(document, "transferable", utils::serialize_asset_transferable(transferable.value()));
    }

    return utils::document_to_string(document);
}

SetTransferable& SetTransferable::set_asset_id(const std::string& asset_id) {
    SetTransferable::asset_id = asset_id;
    return *this;
}

SetTransferable& SetTransferable::set_asset_index(const std::string& asset_index) {
    SetTransferable::asset_index = asset_index;
    return *this;
}

SetTransferable& SetTransferable::set_transferable(models::AssetTransferable transferable) {
    SetTransferable::transferable = transferable;
    return *this;
}

bool SetTransferable::operator==(const SetTransferable& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetTransferable>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetTransferable>&>(rhs) &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           transferable == rhs.transferable;
}

bool SetTransferable::operator!=(const SetTransferable& rhs) const {
    return !(rhs == *this);
}

}
