#include "enjinsdk/shared/CancelTransaction.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

CancelTransaction::CancelTransaction() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.CancelTransaction") {
}

std::string CancelTransaction::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (id.has_value()) {
        utils::set_integer_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

CancelTransaction& CancelTransaction::set_id(int id) {
    CancelTransaction::id = id;
    return *this;
}

bool CancelTransaction::operator==(const CancelTransaction& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           id == rhs.id;
}

bool CancelTransaction::operator!=(const CancelTransaction& rhs) const {
    return !(rhs == *this);
}

}
