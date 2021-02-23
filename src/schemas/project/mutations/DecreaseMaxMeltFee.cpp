#include "enjinsdk/project/DecreaseMaxMeltFee.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

DecreaseMaxMeltFee::DecreaseMaxMeltFee() : graphql::AbstractGraphqlRequest("enjin.sdk.project.DecreaseMaxMeltFee") {
}

std::string DecreaseMaxMeltFee::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, "assetIndex", asset_index.value());
    }
    if (max_melt_fee.has_value()) {
        utils::set_integer_member(document, "maxMeltFee", max_melt_fee.value());
    }

    return utils::document_to_string(document);
}

DecreaseMaxMeltFee& DecreaseMaxMeltFee::set_asset_id(const std::string& asset_id) {
    DecreaseMaxMeltFee::asset_id = asset_id;
    return *this;
}

DecreaseMaxMeltFee& DecreaseMaxMeltFee::set_asset_index(const std::string& asset_index) {
    DecreaseMaxMeltFee::asset_index = asset_index;
    return *this;
}

DecreaseMaxMeltFee& DecreaseMaxMeltFee::set_max_melt_fee(int max_melt_fee) {
    DecreaseMaxMeltFee::max_melt_fee = max_melt_fee;
    return *this;
}

bool DecreaseMaxMeltFee::operator==(const DecreaseMaxMeltFee& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<DecreaseMaxMeltFee>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<DecreaseMaxMeltFee>&>(rhs) &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           max_melt_fee == rhs.max_melt_fee;
}

bool DecreaseMaxMeltFee::operator!=(const DecreaseMaxMeltFee& rhs) const {
    return !(rhs == *this);
}

}
