#include "enjinsdk/shared/GetRequests.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetRequests::GetRequests() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetRequests") {
}

std::string GetRequests::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_objects_to_document(document, {
            TransactionFragmentArguments::serialize(),
            PaginationArguments::serialize()
    });

    if (filter.has_value()) {
        utils::set_object_member_from_type<models::TransactionFilter>(document, "filter", filter.value());
    }
    if (sort.has_value()) {
        utils::set_object_member_from_type<models::TransactionSort>(document, "sort", sort.value());
    }

    return utils::document_to_string(document);
}

GetRequests& GetRequests::set_filter(const models::TransactionFilter& filter) {
    GetRequests::filter = filter;
    return *this;
}

GetRequests& GetRequests::set_sort(const models::TransactionSort& sort) {
    GetRequests::sort = sort;
    return *this;
}

bool GetRequests::operator==(const GetRequests& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionFragmentArguments<GetRequests>&>(*this) ==
           static_cast<const TransactionFragmentArguments<GetRequests>&>(rhs) &&
           static_cast<const PaginationArguments<GetRequests>&>(*this) ==
           static_cast<const PaginationArguments<GetRequests>&>(rhs) &&
           filter == rhs.filter &&
           sort == rhs.sort;
}

bool GetRequests::operator!=(const GetRequests& rhs) const {
    return !(rhs == *this);
}

}
