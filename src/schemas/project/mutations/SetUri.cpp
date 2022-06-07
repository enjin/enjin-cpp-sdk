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

#include "enjinsdk/project/SetUri.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

SetUri::SetUri() : AbstractGraphqlRequest("enjin.sdk.project.SetUri"),
                   ProjectTransactionRequestArguments<SetUri>() {
}

std::string SetUri::serialize() const {
    return to_json().to_string();
}

SetUri& SetUri::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

SetUri& SetUri::set_asset_index(std::string asset_index) {
    asset_index_opt = std::move(asset_index);
    return *this;
}

SetUri& SetUri::set_uri(std::string uri) {
    uri_opt = std::move(uri);
    return *this;
}

JsonValue SetUri::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<SetUri>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "assetIndex", asset_index_opt);
    JsonUtils::try_set_field(json, "uri", uri_opt);

    return json;
}

bool SetUri::operator==(const SetUri& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<SetUri>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt
           && asset_index_opt == rhs.asset_index_opt
           && uri_opt == rhs.uri_opt;
}

bool SetUri::operator!=(const SetUri& rhs) const {
    return !(*this == rhs);
}
