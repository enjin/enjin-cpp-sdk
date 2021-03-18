#include "enjinsdk/shared/GetAssets.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetAssets::GetAssets() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetAssets") {
}

std::string GetAssets::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_objects_to_document(document, {
            AssetFragmentArguments::serialize(),
            PaginationArguments::serialize()
    });

    if (filter.has_value()) {
        utils::set_object_member_from_type<models::AssetFilter>(document, "filter", filter.value());
    }
    if (sort.has_value()) {
        utils::set_object_member_from_type<models::AssetSort>(document, "sort", sort.value());
    }

    return utils::document_to_string(document);
}

GetAssets& GetAssets::set_filter(const models::AssetFilter& filter) {
    GetAssets::filter = filter;
    return *this;
}

GetAssets& GetAssets::set_sort(const models::AssetSort& sort) {
    GetAssets::sort = sort;
    return *this;
}

bool GetAssets::operator==(const GetAssets& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const AssetFragmentArguments<GetAssets>&>(*this) ==
           static_cast<const AssetFragmentArguments<GetAssets>&>(rhs) &&
           static_cast<const PaginationArguments<GetAssets>&>(*this) ==
           static_cast<const PaginationArguments<GetAssets>&>(rhs) &&
           filter == rhs.filter &&
           sort == rhs.sort;
}

bool GetAssets::operator!=(const GetAssets& rhs) const {
    return !(rhs == *this);
}

}
