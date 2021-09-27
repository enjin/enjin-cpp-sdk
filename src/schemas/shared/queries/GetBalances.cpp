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

#include "enjinsdk/shared/GetBalances.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetBalances::GetBalances() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetBalances") {
}

std::string GetBalances::serialize() const {
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
