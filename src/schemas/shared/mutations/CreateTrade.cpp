#include "enjinsdk/shared/CreateTrade.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

CreateTrade::CreateTrade() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.CreateTrade") {

}

std::string CreateTrade::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (asking_assets.has_value()) {
        utils::set_array_member_from_type_vector<models::Trade>(document, "askingAssets", asking_assets.value());
    }
    if (offering_assets.has_value()) {
        utils::set_array_member_from_type_vector<models::Trade>(document, "offeringAssets", offering_assets.value());
    }
    if (recipient_address.has_value()) {
        utils::set_string_member(document, "recipientAddress", recipient_address.value());
    }

    return utils::document_to_string(document);
}

CreateTrade& CreateTrade::set_asking_assets(std::vector<models::Trade> assets) {
    asking_assets = assets;
    return *this;
}

CreateTrade& CreateTrade::set_offering_assets(std::vector<models::Trade> assets) {
    offering_assets = assets;
    return *this;
}

CreateTrade& CreateTrade::set_recipient_address(const std::string& recipient_address) {
    CreateTrade::recipient_address = recipient_address;
    return *this;
}

bool CreateTrade::operator==(const CreateTrade& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArguments<CreateTrade>&>(*this) ==
           static_cast<const TransactionRequestArguments<CreateTrade>&>(rhs) &&
           asking_assets == rhs.asking_assets &&
           offering_assets == rhs.offering_assets &&
           recipient_address == rhs.recipient_address;
}

bool CreateTrade::operator!=(const CreateTrade& rhs) const {
    return !(rhs == *this);
}

}
