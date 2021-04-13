#include "enjinsdk/shared/GetRequest.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetRequest::GetRequest() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetRequest") {
}

std::string GetRequest::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionFragmentArguments::serialize());

    if (id.has_value()) {
        utils::set_integer_member(document, "id", id.value());
    }
    if (transaction_id.has_value()) {
        utils::set_string_member(document, "transactionId", transaction_id.value());
    }

    return utils::document_to_string(document);
}

GetRequest& GetRequest::set_id(int id) {
    GetRequest::id = id;
    return *this;
}

GetRequest& GetRequest::set_transaction_id(const std::string& id) {
    transaction_id = id;
    return *this;
}

bool GetRequest::operator==(const GetRequest& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionFragmentArguments<GetRequest>&>(*this) ==
           static_cast<const TransactionFragmentArguments<GetRequest>&>(rhs) &&
           id == rhs.id &&
           transaction_id == rhs.transaction_id;
}

bool GetRequest::operator!=(const GetRequest& rhs) const {
    return !(rhs == *this);
}

}
