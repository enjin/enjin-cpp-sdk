/* Copyright 2021 Enjin Pte Ltd.
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

#include "enjinsdk/shared/MeltAsset.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

MeltAsset::MeltAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.MeltAsset") {
}

std::string MeltAsset::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArguments::serialize());

    if (melts.has_value()) {
        utils::set_array_member_from_type_vector<models::Melt>(document, "melts", melts.value());
    }

    return utils::document_to_string(document);
}

MeltAsset& MeltAsset::set_melts(std::vector<models::Melt> melts) {
    MeltAsset::melts = melts;
    return *this;
}

bool MeltAsset::operator==(const MeltAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArguments<MeltAsset>&>(*this) ==
           static_cast<const TransactionRequestArguments<MeltAsset>&>(rhs) &&
           melts == rhs.melts;
}

bool MeltAsset::operator!=(const MeltAsset& rhs) const {
    return !(rhs == *this);
}

}
