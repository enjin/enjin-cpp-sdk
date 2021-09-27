/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "enjinsdk/shared/GetAssets.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetAssets::GetAssets() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetAssets") {
}

std::string GetAssets::serialize() const {
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
