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

#include "enjinsdk/project/SetMeltFee.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

SetMeltFee::SetMeltFee() : AbstractGraphqlRequest("enjin.sdk.project.SetMeltFee"),
                           ProjectTransactionRequestArguments<SetMeltFee>() {
}

std::string SetMeltFee::serialize() const {
    return to_json().to_string();
}

SetMeltFee& SetMeltFee::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

SetMeltFee& SetMeltFee::set_melt_fee(int melt_fee) {
    melt_fee_opt = melt_fee;
    return *this;
}

JsonValue SetMeltFee::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, ProjectTransactionRequestArguments<SetMeltFee>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "meltFee", melt_fee_opt);

    return json;
}

bool SetMeltFee::operator==(const SetMeltFee& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<SetMeltFee>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt
           && melt_fee_opt == rhs.melt_fee_opt;
}

bool SetMeltFee::operator!=(const SetMeltFee& rhs) const {
    return !(*this == rhs);
}
