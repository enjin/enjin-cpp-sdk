#include "enjinsdk/project/ReleaseReserve.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

ReleaseReserve::ReleaseReserve() : graphql::AbstractGraphqlRequest("enjin.sdk.project.ReleaseReserve") {
}

std::string ReleaseReserve::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (asset_id.has_value()) {
        utils::set_string_member(document, "assetId", asset_id.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, "value", value.value());
    }

    return utils::document_to_string(document);
}

ReleaseReserve& ReleaseReserve::set_asset_id(const std::string& asset_id) {
    ReleaseReserve::asset_id = asset_id;
    return *this;
}

ReleaseReserve& ReleaseReserve::set_value(const std::string& value) {
    ReleaseReserve::value = value;
    return *this;
}

bool ReleaseReserve::operator==(const ReleaseReserve& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArguments<ReleaseReserve>&>(*this) ==
           static_cast<const shared::TransactionRequestArguments<ReleaseReserve>&>(rhs) &&
           asset_id == rhs.asset_id &&
           value == rhs.value;
}

bool ReleaseReserve::operator!=(const ReleaseReserve& rhs) const {
    return !(rhs == *this);
}

}
