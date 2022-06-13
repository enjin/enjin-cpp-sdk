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

#include "enjinsdk/project/DecreaseMaxTransferFee.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

DecreaseMaxTransferFee::DecreaseMaxTransferFee() : AbstractGraphqlRequest("enjin.sdk.project.DecreaseMaxTransferFee"),
                                                   TransactionRequestArguments<DecreaseMaxTransferFee>() {
}

std::string DecreaseMaxTransferFee::serialize() const {
    return to_json().to_string();
}

DecreaseMaxTransferFee& DecreaseMaxTransferFee::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

DecreaseMaxTransferFee& DecreaseMaxTransferFee::set_max_transfer_fee(int max_transfer_fee) {
    max_transfer_fee_opt = max_transfer_fee;
    return *this;
}

JsonValue DecreaseMaxTransferFee::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionRequestArguments<DecreaseMaxTransferFee>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "maxTransferFee", max_transfer_fee_opt);

    return json;
}

bool DecreaseMaxTransferFee::operator==(const DecreaseMaxTransferFee& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionRequestArguments<DecreaseMaxTransferFee>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt
           && max_transfer_fee_opt == rhs.max_transfer_fee_opt;
}

bool DecreaseMaxTransferFee::operator!=(const DecreaseMaxTransferFee& rhs) const {
    return !(rhs == *this);
}
