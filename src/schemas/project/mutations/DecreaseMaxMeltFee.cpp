#include "enjinsdk/project/DecreaseMaxMeltFee.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

DecreaseMaxMeltFee::DecreaseMaxMeltFee() : graphql::AbstractGraphqlRequest("enjin.sdk.project.DecreaseMaxMeltFee") {
}

std::string DecreaseMaxMeltFee::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (token_id.has_value()) {
        utils::set_string_member(document, "tokenId", token_id.value());
    }
    if (token_index.has_value()) {
        utils::set_string_member(document, "tokenIndex", token_index.value());
    }
    if (max_melt_fee.has_value()) {
        utils::set_integer_member(document, "maxMeltFee", max_melt_fee.value());
    }

    return utils::document_to_string(document);
}

DecreaseMaxMeltFee& DecreaseMaxMeltFee::set_token_id(const std::string& token_id) {
    DecreaseMaxMeltFee::token_id = token_id;
    return *this;
}

DecreaseMaxMeltFee& DecreaseMaxMeltFee::set_token_index(const std::string& token_index) {
    DecreaseMaxMeltFee::token_index = token_index;
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
           token_id == rhs.token_id &&
           token_index == rhs.token_index &&
           max_melt_fee == rhs.max_melt_fee;
}

bool DecreaseMaxMeltFee::operator!=(const DecreaseMaxMeltFee& rhs) const {
    return !(rhs == *this);
}

}
