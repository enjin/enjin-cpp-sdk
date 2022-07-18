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

#include "enjinsdk/project/CreateAsset.hpp"

#include "enjinsdk/EnumUtils.hpp"
#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::sdk::utils;

CreateAsset::CreateAsset() : AbstractGraphqlRequest("enjin.sdk.project.CreateAsset"),
                             TransactionRequestArguments<CreateAsset>() {
}

std::string CreateAsset::serialize() const {
    return to_json().to_string();
}

CreateAsset& CreateAsset::set_name(std::string name) {
    name_opt = std::move(name);
    return *this;
}

CreateAsset& CreateAsset::set_total_supply(std::string total_supply) {
    total_supply_opt = std::move(total_supply);
    return *this;
}

CreateAsset& CreateAsset::set_initial_reserve(std::string initial_reserve) {
    initial_reserve_opt = std::move(initial_reserve);
    return *this;
}

CreateAsset& CreateAsset::set_supply_model(AssetSupplyModel supply_model) {
    supply_model_opt = supply_model;
    return *this;
}

CreateAsset& CreateAsset::set_melt_value(std::string melt_value) {
    melt_value_opt = std::move(melt_value);
    return *this;
}

CreateAsset& CreateAsset::set_melt_fee_ratio(int melt_fee_ratio) {
    melt_fee_ratio_opt = melt_fee_ratio;
    return *this;
}

CreateAsset& CreateAsset::set_transferable(AssetTransferable transferable) {
    transferable_opt = transferable;
    return *this;
}

CreateAsset& CreateAsset::set_transfer_fee_settings(AssetTransferFeeSettingsInput transfer_fee_settings) {
    transfer_fee_settings_opt = std::move(transfer_fee_settings);
    return *this;
}

CreateAsset& CreateAsset::set_non_fungible(bool non_fungible) {
    non_fungible_opt = non_fungible;
    return *this;
}

JsonValue CreateAsset::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionRequestArguments<CreateAsset>::to_json());
    JsonUtils::try_set_field(json, "name", name_opt);
    JsonUtils::try_set_field(json, "totalSupply", total_supply_opt);
    JsonUtils::try_set_field(json, "initialReserve", initial_reserve_opt);
    JsonUtils::try_set_field(json, "supplyModel", supply_model_opt);
    JsonUtils::try_set_field(json, "meltValue", melt_value_opt);
    JsonUtils::try_set_field(json, "meltFeeRatio", melt_fee_ratio_opt);
    JsonUtils::try_set_field(json, "transferable", transferable_opt);
    JsonUtils::try_set_field(json, "transferFeeSettings", transfer_fee_settings_opt);
    JsonUtils::try_set_field(json, "nonFungible", non_fungible_opt);

    return json;
}

bool CreateAsset::operator==(const CreateAsset& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionRequestArguments<CreateAsset>&>(*this) == rhs
           && name_opt == rhs.name_opt
           && total_supply_opt == rhs.total_supply_opt
           && initial_reserve_opt == rhs.initial_reserve_opt
           && supply_model_opt == rhs.supply_model_opt
           && melt_value_opt == rhs.melt_value_opt
           && melt_fee_ratio_opt == rhs.melt_fee_ratio_opt
           && transferable_opt == rhs.transferable_opt
           && transfer_fee_settings_opt == rhs.transfer_fee_settings_opt
           && non_fungible_opt == rhs.non_fungible_opt;
}

bool CreateAsset::operator!=(const CreateAsset& rhs) const {
    return !(*this == rhs);
}
