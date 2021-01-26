#include "enjinsdk/project/SetMeltFee.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

SetMeltFee::SetMeltFee() : graphql::AbstractGraphqlRequest("enjin.sdk.project.SetMeltFee") {
}

std::string SetMeltFee::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (token_id.has_value()) {
        utils::set_string_member(document, "tokenId", token_id.value());
    }
    if (token_index.has_value()) {
        utils::set_string_member(document, "tokenIndex", token_index.value());
    }
    if (melt_fee.has_value()) {
        utils::set_integer_member(document, "meltFee", melt_fee.value());
    }

    return utils::document_to_string(document);
}

SetMeltFee& SetMeltFee::set_token_id(const std::string& token_id) {
    SetMeltFee::token_id = token_id;
    return *this;
}

SetMeltFee& SetMeltFee::set_token_index(const std::string& token_index) {
    SetMeltFee::token_index = token_index;
    return *this;
}

SetMeltFee& SetMeltFee::set_melt_fee(int melt_fee) {
    SetMeltFee::melt_fee = melt_fee;
    return *this;
}

bool SetMeltFee::operator==(const SetMeltFee& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetMeltFee>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<SetMeltFee>&>(rhs) &&
           token_id == rhs.token_id &&
           token_index == rhs.token_index &&
           melt_fee == rhs.melt_fee;
}

bool SetMeltFee::operator!=(const SetMeltFee& rhs) const {
    return !(rhs == *this);
}

}
