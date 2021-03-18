#include "enjinsdk/shared/GetBalances.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetBalances::GetBalances() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetBalances") {
}

std::string GetBalances::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_objects_to_document(document, {
            BalanceFragmentArguments::serialize(),
            PaginationArguments::serialize()
    });

    if (filter.has_value()) {
        utils::set_object_member_from_type<models::BalanceFilter>(document, "filter", filter.value());
    }

    return utils::document_to_string(document);
}

GetBalances& GetBalances::set_filter(models::BalanceFilter filter) {
    GetBalances::filter = filter;
    return *this;
}

bool GetBalances::operator==(const GetBalances& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const BalanceFragmentArguments<GetBalances>&>(*this) ==
           static_cast<const BalanceFragmentArguments<GetBalances>&>(rhs) &&
           static_cast<const PaginationArguments<GetBalances>&>(*this) ==
           static_cast<const PaginationArguments<GetBalances>&>(rhs) &&
           filter == rhs.filter;
}

bool GetBalances::operator!=(const GetBalances& rhs) const {
    return !(rhs == *this);
}

}
