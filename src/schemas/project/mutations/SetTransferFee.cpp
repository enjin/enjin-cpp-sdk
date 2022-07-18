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

#include "enjinsdk/project/SetTransferFee.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

SetTransferFee::SetTransferFee() : AbstractGraphqlRequest("enjin.sdk.project.SetTransferFee"),
                                   TransactionRequestArguments<SetTransferFee>() {
}

std::string SetTransferFee::serialize() const {
    return to_json().to_string();
}

SetTransferFee& SetTransferFee::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

SetTransferFee& SetTransferFee::set_transfer_fee(std::string transfer_fee) {
    transfer_fee_opt = std::move(transfer_fee);
    return *this;
}

JsonValue SetTransferFee::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionRequestArguments<SetTransferFee>::to_json());
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "transferFee", transfer_fee_opt);

    return json;
}

bool SetTransferFee::operator==(const SetTransferFee& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionRequestArguments<SetTransferFee>&>(*this) == rhs
           && asset_id_opt == rhs.asset_id_opt
           && transfer_fee_opt == rhs.transfer_fee_opt;
}

bool SetTransferFee::operator!=(const SetTransferFee& rhs) const {
    return !(*this == rhs);
}
