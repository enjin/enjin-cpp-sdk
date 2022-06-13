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

#include "enjinsdk/project/AdvancedSendAsset.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

AdvancedSendAsset::AdvancedSendAsset() : AbstractGraphqlRequest("enjin.sdk.project.AdvancedSendAsset"),
                                         ProjectTransactionRequestArguments<AdvancedSendAsset>() {
}

std::string AdvancedSendAsset::serialize() const {
    return to_json().to_string();
}

AdvancedSendAsset& AdvancedSendAsset::set_transfers(std::vector<Transfer> transfers) {
    transfers_opt = std::move(transfers);
    return *this;
}

AdvancedSendAsset& AdvancedSendAsset::set_data(std::string data) {
    data_opt = std::move(data);
    return *this;
}

JsonValue AdvancedSendAsset::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<AdvancedSendAsset>::to_json());
    JsonUtils::try_set_field(json, "transfers", transfers_opt);
    JsonUtils::try_set_field(json, "data", data_opt);

    return json;
}

bool AdvancedSendAsset::operator==(const AdvancedSendAsset& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<AdvancedSendAsset>&>(*this) == rhs
           && transfers_opt == rhs.transfers_opt
           && data_opt == rhs.data_opt;
}

bool AdvancedSendAsset::operator!=(const AdvancedSendAsset& rhs) const {
    return !(*this == rhs);
}
