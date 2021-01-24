#include "enjinsdk/shared/MeltToken.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

MeltToken::MeltToken() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.MeltToken") {
}

std::string MeltToken::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

    if (melts.has_value()) {
        utils::set_array_member_from_type_vector<models::Melt>(document, "melts", melts.value());
    }

    return utils::document_to_string(document);
}

MeltToken& MeltToken::set_melts(std::vector<models::Melt> melts) {
    MeltToken::melts = melts;
    return *this;
}

bool MeltToken::operator==(const MeltToken& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArgumentsTemplate<MeltToken>&>(*this) ==
           static_cast<const TransactionRequestArgumentsTemplate<MeltToken>&>(rhs) &&
           melts == rhs.melts;
}

bool MeltToken::operator!=(const MeltToken& rhs) const {
    return !(rhs == *this);
}

}
