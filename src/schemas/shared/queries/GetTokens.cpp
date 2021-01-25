#include "enjinsdk/shared/GetTokens.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetTokens::GetTokens() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetTokens") {
}

std::string GetTokens::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_objects_to_document(document, {
            TokenFragmentArgumentsTemplate::serialize(),
            PaginationArgumentsTemplate::serialize()
    });

    if (filter.has_value()) {
        utils::set_object_member_from_type<models::TokenFilter>(document, "filter", filter.value());
    }
    if (sort.has_value()) {
        utils::set_object_member_from_type<models::TokenSort>(document, "sort", sort.value());
    }

    return utils::document_to_string(document);
}

GetTokens& GetTokens::set_filter(const models::TokenFilter& filter) {
    GetTokens::filter = filter;
    return *this;
}

GetTokens& GetTokens::set_sort(const models::TokenSort& sort) {
    GetTokens::sort = sort;
    return *this;
}

bool GetTokens::operator==(const GetTokens& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TokenFragmentArgumentsTemplate<GetTokens>&>(*this) ==
           static_cast<const TokenFragmentArgumentsTemplate<GetTokens>&>(rhs) &&
           static_cast<const PaginationArgumentsTemplate<GetTokens>&>(*this) ==
           static_cast<const PaginationArgumentsTemplate<GetTokens>&>(rhs) &&
           filter == rhs.filter &&
           sort == rhs.sort;
}

bool GetTokens::operator!=(const GetTokens& rhs) const {
    return !(rhs == *this);
}

}
