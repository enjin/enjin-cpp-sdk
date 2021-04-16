/* Copyright 2021 Enjin Pte Ltd.
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

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string BalanceFilter::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (and_filters.has_value()) {
        utils::set_array_member_from_type_vector<BalanceFilter>(document, AND_KEY, and_filters.value());
    }
    if (or_filters.has_value()) {
        utils::set_array_member_from_type_vector<BalanceFilter>(document, OR_KEY, or_filters.value());
    }
    if (asset_id.has_value()) {
        utils::set_string_member(document, ASSET_ID_KEY, asset_id.value());
    }
    if (asset_id_in.has_value()) {
        utils::set_array_member_from_string_vector(document, ASSET_ID_IN_KEY, asset_id_in.value());
    }
    if (wallet.has_value()) {
        utils::set_string_member(document, WALLET_KEY, wallet.value());
    }
    if (wallet_in.has_value()) {
        utils::set_array_member_from_string_vector(document, WALLET_IN_KEY, wallet_in.value());
    }
    if (value.has_value()) {
        utils::set_integer_member(document, VALUE_KEY, value.value());
    }
    if (value_gt.has_value()) {
        utils::set_integer_member(document, VALUE_GT_KEY, value_gt.value());
    }
    if (value_gte.has_value()) {
        utils::set_integer_member(document, VALUE_GTE_KEY, value_gte.value());
    }
    if (value_lt.has_value()) {
        utils::set_integer_member(document, VALUE_LT_KEY, value_lt.value());
    }
    if (value_lte.has_value()) {
        utils::set_integer_member(document, VALUE_LTE_KEY, value_lte.value());
    }

    return utils::document_to_string(document);
}

BalanceFilter& BalanceFilter::set_and(const std::vector<BalanceFilter>& others) {
    and_filters = others;
    return *this;
}

BalanceFilter& BalanceFilter::set_or(const std::vector<BalanceFilter>& others) {
    or_filters = others;
    return *this;
}

BalanceFilter& BalanceFilter::set_asset_id(const std::string& asset_id) {
    BalanceFilter::asset_id = asset_id;
    return *this;
}

BalanceFilter& BalanceFilter::set_asset_id_in(const std::vector<std::string>& asset_ids) {
    asset_id_in = asset_ids;
    return *this;
}

BalanceFilter& BalanceFilter::set_wallet(const std::string& wallet) {
    BalanceFilter::wallet = wallet;
    return *this;
}

BalanceFilter& BalanceFilter::set_wallet_in(const std::vector<std::string>& wallets) {
    wallet_in = wallets;
    return *this;
}

BalanceFilter& BalanceFilter::set_value(int value) {
    BalanceFilter::value = value;
    return *this;
}

BalanceFilter& BalanceFilter::set_value_greater_than(int value) {
    value_gt = value;
    return *this;
}

BalanceFilter& BalanceFilter::set_value_greater_than_or_equal(int value) {
    value_gte = value;
    return *this;
}

BalanceFilter& BalanceFilter::set_value_less_than(int value) {
    value_lt = value;
    return *this;
}

BalanceFilter& BalanceFilter::set_value_less_than_or_equal(int value) {
    value_lte = value;
    return *this;
}

bool BalanceFilter::operator==(const BalanceFilter& rhs) const {
    return and_filters == rhs.and_filters &&
           or_filters == rhs.or_filters &&
           asset_id == rhs.asset_id &&
           asset_id_in == rhs.asset_id_in &&
           wallet == rhs.wallet &&
           wallet_in == rhs.wallet_in &&
           value == rhs.value &&
           value_gt == rhs.value_gt &&
           value_gte == rhs.value_gte &&
           value_lt == rhs.value_lt &&
           value_lte == rhs.value_lte;
}

bool BalanceFilter::operator!=(const BalanceFilter& rhs) const {
    return !(rhs == *this);
}

}
