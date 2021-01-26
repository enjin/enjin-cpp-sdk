#include "enjinsdk/project/DecreaseMaxTransferFee.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

DecreaseMaxTransferFee::DecreaseMaxTransferFee()
        : graphql::AbstractGraphqlRequest("enjin.sdk.project.DecreaseMaxTransferFee") {
}

std::string DecreaseMaxTransferFee::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (token_id.has_value()) {
        utils::set_string_member(document, "tokenId", token_id.value());
    }
    if (token_index.has_value()) {
        utils::set_string_member(document, "tokenIndex", token_index.value());
    }
    if (max_transfer_fee.has_value()) {
        utils::set_integer_member(document, "maxTransferFee", max_transfer_fee.value());
    }

    return utils::document_to_string(document);
}

DecreaseMaxTransferFee& DecreaseMaxTransferFee::set_token_id(const std::string& token_id) {
    DecreaseMaxTransferFee::token_id = token_id;
    return *this;
}

DecreaseMaxTransferFee& DecreaseMaxTransferFee::set_token_index(const std::string& token_index) {
    DecreaseMaxTransferFee::token_index = token_index;
    return *this;
}

DecreaseMaxTransferFee& DecreaseMaxTransferFee::set_max_transfer_fee(int max_transfer_fee) {
    DecreaseMaxTransferFee::max_transfer_fee = max_transfer_fee;
    return *this;
}

bool DecreaseMaxTransferFee::operator==(const DecreaseMaxTransferFee& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<DecreaseMaxTransferFee>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<DecreaseMaxTransferFee>&>(rhs) &&
           token_id == rhs.token_id &&
           token_index == rhs.token_index &&
           max_transfer_fee == rhs.max_transfer_fee;
}

bool DecreaseMaxTransferFee::operator!=(const DecreaseMaxTransferFee& rhs) const {
    return !(rhs == *this);
}

}
