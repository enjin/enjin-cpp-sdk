#include "enjinsdk/project/SetUri.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetUri::SetUri() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetUri") {
}

std::string SetUri::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
    }
    if (uri.has_value()) {
        utils::set_string_member(document, "uri", uri.value());
    }

    return utils::document_to_string(document);
}

SetUri& SetUri::set_asset_id(const std::string& asset_id) {
    SetUri::asset_id = asset_id;
    return *this;
}

SetUri& SetUri::set_asset_index(const std::string& asset_index) {
    SetUri::asset_index = asset_index;
    return *this;
}

SetUri& SetUri::set_uri(const std::string& uri) {
    SetUri::uri = uri;
    return *this;
}

bool SetUri::operator==(const SetUri& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArguments<SetUri>&>(*this) ==
           static_cast<const shared::TransactionRequestArguments<SetUri>&>(rhs) &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           uri == rhs.uri;
}

bool SetUri::operator!=(const SetUri& rhs) const {
    return !(rhs == *this);
}

}
