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

#include "enjinsdk/shared/GetRequests.hpp"

#include "RapidJsonUtils.hpp"
#include <utility>

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

GetRequests& GetRequests::set_filter(models::TransactionFilter filter) {
    GetRequests::filter = std::move(filter);
    return *this;
}

GetRequests& GetRequests::set_sort(models::TransactionSort sort) {
    GetRequests::sort = std::move(sort);
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
