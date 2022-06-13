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

#include "enjinsdk/project/MeltAsset.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

MeltAsset::MeltAsset() : AbstractGraphqlRequest("enjin.sdk.project.MeltAsset"),
                         TransactionRequestArguments<MeltAsset>() {
}

std::string MeltAsset::serialize() const {
    return to_json().to_string();
}

MeltAsset& MeltAsset::set_melts(std::vector<MeltInput> melts) {
    melts_opt = std::move(melts);
    return *this;
}

JsonValue MeltAsset::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionRequestArguments<MeltAsset>::to_json());
    JsonUtils::try_set_field(json, "melts", melts_opt);

    return json;
}

bool MeltAsset::operator==(const MeltAsset& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionRequestArguments<MeltAsset>&>(*this) == rhs
           && melts_opt == rhs.melts_opt;
}

bool MeltAsset::operator!=(const MeltAsset& rhs) const {
    return !(*this == rhs);
}
