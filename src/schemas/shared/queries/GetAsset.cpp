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

#include "enjinsdk/shared/GetAsset.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetAsset::GetAsset() : AbstractGraphqlRequest("enjin.sdk.shared.GetAsset"),
                       AssetFragmentArguments<GetAsset>() {
}

std::string GetAsset::serialize() const {
    return to_json().to_string();
}

GetAsset& GetAsset::set_id(std::string id) {
    id_opt = std::move(id);
    return *this;
}

JsonValue GetAsset::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, AssetFragmentArguments<GetAsset>::to_json());
    JsonUtils::try_set_field(json, "id", id_opt);

    return json;
}

bool GetAsset::operator==(const GetAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const AssetFragmentArguments<GetAsset>&>(*this) == rhs
           && id_opt == rhs.id_opt;
}

bool GetAsset::operator!=(const GetAsset& rhs) const {
    return !(rhs == *this);
}
