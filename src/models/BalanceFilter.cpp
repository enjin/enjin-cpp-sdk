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

#include "enjinsdk/models/BalanceFilter.hpp"

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

std::string BalanceFilter::serialize() const {
    return to_json().to_string();
}

BalanceFilter& BalanceFilter::set_and(std::vector<BalanceFilter> others) {
    and_filters_opt = std::move(others);
    return *this;
}

BalanceFilter& BalanceFilter::set_or(std::vector<BalanceFilter> others) {
    or_filters_opt = std::move(others);
    return *this;
}

BalanceFilter& BalanceFilter::set_asset_id(std::string asset_id) {
    asset_id_opt = std::move(asset_id);
    return *this;
}

BalanceFilter& BalanceFilter::set_asset_id_in(std::vector<std::string> asset_ids) {
    asset_id_in_opt = std::move(asset_ids);
    return *this;
}

BalanceFilter& BalanceFilter::set_wallet(std::string wallet) {
    wallet_opt = std::move(wallet);
    return *this;
}

BalanceFilter& BalanceFilter::set_wallet_in(std::vector<std::string> wallets) {
    wallet_in_opt = std::move(wallets);
    return *this;
}

BalanceFilter& BalanceFilter::set_value(int value) {
    value_opt = value;
    return *this;
}

BalanceFilter& BalanceFilter::set_value_is(Operator value_is) {
    value_is_opt = value_is;
    return *this;
}

JsonValue BalanceFilter::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::try_set_field(json, "and", and_filters_opt);
    JsonUtils::try_set_field(json, "or", or_filters_opt);
    JsonUtils::try_set_field(json, "assetId", asset_id_opt);
    JsonUtils::try_set_field(json, "assetId_in", asset_id_in_opt);
    JsonUtils::try_set_field(json, "wallet", wallet_opt);
    JsonUtils::try_set_field(json, "wallet_in", wallet_in_opt);
    JsonUtils::try_set_field(json, "value", value_opt);
    JsonUtils::try_set_field(json, "value_is", value_is_opt);

    return json;
}

bool BalanceFilter::operator==(const BalanceFilter& rhs) const {
    return and_filters_opt == rhs.and_filters_opt
           && or_filters_opt == rhs.or_filters_opt
           && asset_id_opt == rhs.asset_id_opt
           && asset_id_in_opt == rhs.asset_id_in_opt
           && wallet_opt == rhs.wallet_opt
           && wallet_in_opt == rhs.wallet_in_opt
           && value_opt == rhs.value_opt
           && value_is_opt == rhs.value_is_opt;
}

bool BalanceFilter::operator!=(const BalanceFilter& rhs) const {
    return !(*this == rhs);
}
