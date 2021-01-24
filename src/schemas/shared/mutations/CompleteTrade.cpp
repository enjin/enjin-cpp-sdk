#include "enjinsdk/shared/CompleteTrade.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

CompleteTrade::CompleteTrade() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.CompleteTrade") {
}

std::string CompleteTrade::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (trade_id.has_value()) {
        utils::set_string_member(document, "tradeId", trade_id.value());
    }

    return utils::document_to_string(document);
}

CompleteTrade& CompleteTrade::set_trade_id(const std::string& id) {
    trade_id = id;
    return *this;
}

bool CompleteTrade::operator==(const CompleteTrade& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArgumentsTemplate<CompleteTrade>&>(*this) ==
           static_cast<const TransactionRequestArgumentsTemplate<CompleteTrade>&>(rhs) &&
           trade_id == rhs.trade_id;
}

bool CompleteTrade::operator!=(const CompleteTrade& rhs) const {
    return !(rhs == *this);
}

}
