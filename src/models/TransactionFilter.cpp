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

#include "enjinsdk/models/TransactionFilter.hpp"

#include "RapidJsonUtils.hpp"
#include "enjinsdk/EnumUtils.hpp"

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

std::string TransactionFilter::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (and_filters.has_value()) {
        set_array_member_from_type_vector<TransactionFilter>(document, AND_KEY, and_filters.value());
    }

    if (or_filters.has_value()) {
        set_array_member_from_type_vector<TransactionFilter>(document, OR_KEY, or_filters.value());
    }

    if (id.has_value()) {
        set_string_member(document, ID_KEY, id.value());
    }

    if (id_in.has_value()) {
        set_array_member_from_string_vector(document, ID_IN_KEY, id_in.value());
    }

    if (transaction_id.has_value()) {
        set_string_member(document, TRANSACTION_ID_KEY, transaction_id.value());
    }

    if (transaction_id_in.has_value()) {
        set_array_member_from_string_vector(document, TRANSACTION_ID_IN_KEY, transaction_id_in.value());
    }

    if (asset_id.has_value()) {
        set_string_member(document, ASSET_ID_KEY, asset_id.value());
    }

    if (asset_id_in.has_value()) {
        set_array_member_from_string_vector(document, ASSET_ID_IN_KEY, asset_id_in.value());
    }

    if (type.has_value()) {
        set_string_member(document, TYPE_KEY, EnumUtils::serialize_request_type(type.value()));
    }

    if (type_in.has_value()) {
        std::vector<std::string> v;
        for (auto& e: type_in.value()) {
            v.push_back(EnumUtils::serialize_request_type(e));
        }

        set_array_member_from_string_vector(document, TYPE_IN_KEY, v);
    }

    if (value.has_value()) {
        set_integer_member(document, VALUE_KEY, value.value());
    }

    if (value_gt.has_value()) {
        set_integer_member(document, VALUE_GT_KEY, value_gt.value());
    }

    if (value_gte.has_value()) {
        set_integer_member(document, VALUE_GTE_KEY, value_gte.value());
    }

    if (value_lt.has_value()) {
        set_integer_member(document, VALUE_LT_KEY, value_lt.value());
    }

    if (value_lte.has_value()) {
        set_integer_member(document, VALUE_LTE_KEY, value_lte.value());
    }

    if (state.has_value()) {
        set_string_member(document, STATE_KEY, EnumUtils::serialize_request_state(state.value()));
    }

    if (state_in.has_value()) {
        std::vector<std::string> v;
        for (auto& e: state_in.value()) {
            v.push_back(EnumUtils::serialize_request_state(e));
        }

        set_array_member_from_string_vector(document, STATE_IN_KEY, v);
    }

    if (wallet.has_value()) {
        set_string_member(document, WALLET_KEY, wallet.value());
    }

    if (wallet_in.has_value()) {
        set_array_member_from_string_vector(document, WALLET_IN_KEY, wallet_in.value());
    }

    return document_to_string(document);
}

TransactionFilter& TransactionFilter::set_and(std::vector<TransactionFilter> others) {
    and_filters = std::move(others);
    return *this;
}

TransactionFilter& TransactionFilter::set_or(std::vector<TransactionFilter> others) {
    or_filters = std::move(others);
    return *this;
}

TransactionFilter& TransactionFilter::set_id(std::string id) {
    TransactionFilter::id = std::move(id);
    return *this;
}

TransactionFilter& TransactionFilter::set_id_in(std::vector<std::string> ids) {
    id_in = std::move(ids);
    return *this;
}

TransactionFilter& TransactionFilter::set_transaction_id(std::string transaction_id) {
    TransactionFilter::transaction_id = std::move(transaction_id);
    return *this;
}

TransactionFilter& TransactionFilter::set_transaction_id_in(std::vector<std::string> transaction_ids) {
    transaction_id_in = std::move(transaction_ids);
    return *this;
}

TransactionFilter& TransactionFilter::set_asset_id(std::string asset_id) {
    TransactionFilter::asset_id = std::move(asset_id);
    return *this;
}

TransactionFilter& TransactionFilter::set_asset_id_in(std::vector<std::string> asset_ids) {
    asset_id_in = std::move(asset_ids);
    return *this;
}

TransactionFilter& TransactionFilter::set_type(RequestType type) {
    TransactionFilter::type = type;
    return *this;
}

TransactionFilter& TransactionFilter::set_type_in(std::vector<RequestType> types) {
    type_in = std::move(types);
    return *this;
}

TransactionFilter& TransactionFilter::set_value(int value) {
    TransactionFilter::value = value;
    return *this;
}

TransactionFilter& TransactionFilter::set_value_gt(int value) {
    value_gt = value;
    return *this;
}

TransactionFilter& TransactionFilter::set_value_gte(int value) {
    value_gte = value;
    return *this;
}

TransactionFilter& TransactionFilter::set_value_lt(int value) {
    value_lt = value;
    return *this;
}

TransactionFilter& TransactionFilter::set_value_lte(int value) {
    value_lte = value;
    return *this;
}

TransactionFilter& TransactionFilter::set_state(RequestState state) {
    TransactionFilter::state = state;
    return *this;
}

TransactionFilter& TransactionFilter::set_state_in(std::vector<RequestState> states) {
    state_in = std::move(states);
    return *this;
}

TransactionFilter& TransactionFilter::set_wallet(std::string wallet) {
    TransactionFilter::wallet = std::move(wallet);
    return *this;
}

TransactionFilter& TransactionFilter::set_wallet_in(std::vector<std::string> wallets) {
    wallet_in = std::move(wallets);
    return *this;
}

bool TransactionFilter::operator==(const TransactionFilter& rhs) const {
    return and_filters == rhs.and_filters
           && or_filters == rhs.or_filters
           && id == rhs.id
           && id_in == rhs.id_in
           && transaction_id == rhs.transaction_id
           && transaction_id_in == rhs.transaction_id_in
           && asset_id == rhs.asset_id
           && asset_id_in == rhs.asset_id_in
           && type == rhs.type
           && type_in == rhs.type_in
           && value == rhs.value
           && value_gt == rhs.value_gt
           && value_gte == rhs.value_gte
           && value_lt == rhs.value_lt
           && value_lte == rhs.value_lte
           && state == rhs.state
           && state_in == rhs.state_in
           && wallet == rhs.wallet
           && wallet_in == rhs.wallet_in;
}

bool TransactionFilter::operator!=(const TransactionFilter& rhs) const {
    return !(rhs == *this);
}
