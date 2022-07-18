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

#include "enjinsdk/project/InvalidateAssetMetadata.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

InvalidateAssetMetadata::InvalidateAssetMetadata()
        : AbstractGraphqlRequest("enjin.sdk.project.InvalidateAssetMetadata") {
}

std::string InvalidateAssetMetadata::serialize() const {
    return to_json().to_string();
}

InvalidateAssetMetadata& InvalidateAssetMetadata::set_id(std::string id) {
    id_opt = std::move(id);
    return *this;
}

JsonValue InvalidateAssetMetadata::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::try_set_field(json, "id", id_opt);

    return json;
}

bool InvalidateAssetMetadata::operator==(const InvalidateAssetMetadata& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && id_opt == rhs.id_opt;
}

bool InvalidateAssetMetadata::operator!=(const InvalidateAssetMetadata& rhs) const {
    return !(*this == rhs);
}
