#include "enjinsdk/project/SetMeltFee.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetMeltFee::SetMeltFee() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetMeltFee") {
}

std::string SetMeltFee::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
    }
    if (melt_fee.has_value()) {
        utils::set_integer_member(document, "meltFee", melt_fee.value());
    }

    return utils::document_to_string(document);
}

SetMeltFee& SetMeltFee::set_asset_id(const std::string& asset_id) {
    SetMeltFee::asset_id = asset_id;
    return *this;
}

SetMeltFee& SetMeltFee::set_asset_index(const std::string& asset_index) {
    SetMeltFee::asset_index = asset_index;
    return *this;
}

SetMeltFee& SetMeltFee::set_melt_fee(int melt_fee) {
    SetMeltFee::melt_fee = melt_fee;
    return *this;
}

bool SetMeltFee::operator==(const SetMeltFee& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArguments<SetMeltFee>&>(*this) ==
           static_cast<const shared::TransactionRequestArguments<SetMeltFee>&>(rhs) &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           melt_fee == rhs.melt_fee;
}

bool SetMeltFee::operator!=(const SetMeltFee& rhs) const {
    return !(rhs == *this);
}

}
