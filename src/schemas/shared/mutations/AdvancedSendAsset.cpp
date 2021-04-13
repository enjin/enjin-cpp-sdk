#include "enjinsdk/shared/AdvancedSendAsset.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

AdvancedSendAsset::AdvancedSendAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.AdvancedSendAsset") {
}

std::string AdvancedSendAsset::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (transfers.has_value()) {
        utils::set_array_member_from_type_vector<models::Transfer>(document, "transfers", transfers.value());
    }
    if (data.has_value()) {
        utils::set_string_member(document, "data", data.value());
    }

    return utils::document_to_string(document);
}

AdvancedSendAsset& AdvancedSendAsset::set_transfers(const std::vector<models::Transfer>& transfers) {
    AdvancedSendAsset::transfers = transfers;
    return *this;
}

AdvancedSendAsset& AdvancedSendAsset::set_data(const std::string& data) {
    AdvancedSendAsset::data = data;
    return *this;
}

bool AdvancedSendAsset::operator==(const AdvancedSendAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArguments<AdvancedSendAsset>&>(*this) ==
           static_cast<const TransactionRequestArguments<AdvancedSendAsset>&>(rhs) &&
           transfers == rhs.transfers &&
           data == rhs.data;
}

bool AdvancedSendAsset::operator!=(const AdvancedSendAsset& rhs) const {
    return !(rhs == *this);
}

}
