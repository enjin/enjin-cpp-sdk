#include "enjinsdk/project/MintAsset.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

MintAsset::MintAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.project.MintAsset") {
}

std::string MintAsset::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (mints.has_value()) {
        utils::set_array_member_from_type_vector<models::MintInput>(document, "mints", mints.value());
    }

    return utils::document_to_string(document);
}

MintAsset& MintAsset::set_asset_id(const std::string& asset_id) {
    MintAsset::asset_id = asset_id;
    return *this;
}

MintAsset& MintAsset::set_mints(const std::vector<models::MintInput>& mints) {
    MintAsset::mints = mints;
    return *this;
}

bool MintAsset::operator==(const MintAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArguments<MintAsset>&>(*this) ==
           static_cast<const shared::TransactionRequestArguments<MintAsset>&>(rhs) &&
           asset_id == rhs.asset_id &&
           mints == rhs.mints;
}

bool MintAsset::operator!=(const MintAsset& rhs) const {
    return !(rhs == *this);
}

}
