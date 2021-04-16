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

#include "enjinsdk/models/TransactionFilter.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string TransactionFilter::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (and_filters.has_value()) {
        utils::set_array_member_from_type_vector<TransactionFilter>(document, AND_KEY, and_filters.value());
    }
    if (or_filters.has_value()) {
        utils::set_array_member_from_type_vector<TransactionFilter>(document, OR_KEY, or_filters.value());
    }
    if (id.has_value()) {
        utils::set_string_member(document, ID_KEY, id.value());
    }
    if (id_in.has_value()) {
        utils::set_array_member_from_string_vector(document, ID_IN_KEY, id_in.value());
    }
    if (transaction_id.has_value()) {
        utils::set_string_member(document, TRANSACTION_ID_KEY, transaction_id.value());
    }
    if (transaction_id_in.has_value()) {
        utils::set_array_member_from_string_vector(document, TRANSACTION_ID_IN_KEY, transaction_id_in.value());
    }
    if (asset_id.has_value()) {
        utils::set_string_member(document, ASSET_ID_KEY, asset_id.value());
    }
    if (asset_id_in.has_value()) {
        utils::set_array_member_from_string_vector(document, ASSET_ID_IN_KEY, asset_id_in.value());
    }
    if (type.has_value()) {
        utils::set_string_member(document, TYPE_KEY, utils::serialize_request_type(type.value()));
    }
    if (type_in.has_value()) {
        std::vector<std::string> v;
        for (auto& e : type_in.value()) {
            v.push_back(utils::serialize_request_type(e));
        }

        utils::set_array_member_from_string_vector(document, TYPE_IN_KEY, v);
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
    if (state.has_value()) {
        utils::set_string_member(document, STATE_KEY, utils::serialize_request_state(state.value()));
    }
    if (state_in.has_value()) {
        std::vector<std::string> v;
        for (auto& e : state_in.value()) {
            v.push_back(utils::serialize_request_state(e));
        }

        utils::set_array_member_from_string_vector(document, STATE_IN_KEY, v);
    }
    if (wallet.has_value()) {
        utils::set_string_member(document, WALLET_KEY, wallet.value());
    }
    if (wallet_in.has_value()) {
        utils::set_array_member_from_string_vector(document, WALLET_IN_KEY, wallet_in.value());
    }

    return utils::document_to_string(document);
}

TransactionFilter& TransactionFilter::set_and(const std::vector<TransactionFilter>& others) {
    and_filters = others;
    return *this;
}

TransactionFilter& TransactionFilter::set_or(const std::vector<TransactionFilter>& others) {
    or_filters = others;
    return *this;
}

TransactionFilter& TransactionFilter::set_id(const std::string& id) {
    TransactionFilter::id = id;
    return *this;
}

TransactionFilter& TransactionFilter::set_id_in(const std::vector<std::string>& ids) {
    id_in = ids;
    return *this;
}

TransactionFilter& TransactionFilter::set_transaction_id(const std::string& transaction_id) {
    TransactionFilter::transaction_id = transaction_id;
    return *this;
}

TransactionFilter& TransactionFilter::set_transaction_id_in(const std::vector<std::string>& transaction_ids) {
    transaction_id_in = transaction_ids;
    return *this;
}

TransactionFilter& TransactionFilter::set_asset_id(const std::string& asset_id) {
    TransactionFilter::asset_id = asset_id;
    return *this;
}

TransactionFilter& TransactionFilter::set_asset_id_in(const std::vector<std::string>& asset_ids) {
    asset_id_in = asset_ids;
    return *this;
}

TransactionFilter& TransactionFilter::set_type(const RequestType& type) {
    TransactionFilter::type = type;
    return *this;
}

TransactionFilter& TransactionFilter::set_type_in(const std::vector<RequestType>& types) {
    type_in = types;
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

TransactionFilter& TransactionFilter::set_state(const RequestState& state) {
    TransactionFilter::state = state;
    return *this;
}

TransactionFilter& TransactionFilter::set_state_in(const std::vector<RequestState>& states) {
    state_in = states;
    return *this;
}

TransactionFilter& TransactionFilter::set_wallet(const std::string& wallet) {
    TransactionFilter::wallet = wallet;
    return *this;
}

TransactionFilter& TransactionFilter::set_wallet_in(const std::vector<std::string>& wallets) {
    wallet_in = wallets;
    return *this;
}

bool TransactionFilter::operator==(const TransactionFilter& rhs) const {
    return and_filters == rhs.and_filters &&
           or_filters == rhs.or_filters &&
           id == rhs.id &&
           id_in == rhs.id_in &&
           transaction_id == rhs.transaction_id &&
           transaction_id_in == rhs.transaction_id_in &&
           asset_id == rhs.asset_id &&
           asset_id_in == rhs.asset_id_in &&
           type == rhs.type &&
           type_in == rhs.type_in &&
           value == rhs.value &&
           value_gt == rhs.value_gt &&
           value_gte == rhs.value_gte &&
           value_lt == rhs.value_lt &&
           value_lte == rhs.value_lte &&
           state == rhs.state &&
           state_in == rhs.state_in &&
           wallet == rhs.wallet &&
           wallet_in == rhs.wallet_in;
}

bool TransactionFilter::operator!=(const TransactionFilter& rhs) const {
    return !(rhs == *this);
}

}
