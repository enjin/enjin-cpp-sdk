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

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class TransactionFilter::Impl final : public ISerializable {
public:
    Impl() = default;

    ~Impl() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    void set_and(std::vector<TransactionFilter> others) {
        and_filters_opt = std::move(others);
    }

    void set_or(std::vector<TransactionFilter> others) {
        or_filters_opt = std::move(others);
    }

    void set_id(std::string id) {
        id_opt = std::move(id);
    }

    void set_id_in(std::vector<std::string> ids) {
        id_in_opt = std::move(ids);
    }

    void set_transaction_id(std::string transaction_id) {
        transaction_id_opt = std::move(transaction_id);
    }

    void set_transaction_id_in(std::vector<std::string> transaction_ids) {
        transaction_id_in_opt = std::move(transaction_ids);
    }

    void set_asset_id(std::string asset_id) {
        asset_id_opt = std::move(asset_id);
    }

    void set_asset_id_in(std::vector<std::string> asset_ids) {
        asset_id_in_opt = std::move(asset_ids);
    }

    void set_type(TransactionType type) {
        type_opt = type;
    }

    void set_type_in(std::vector<TransactionType> types) {
        type_in_opt = std::move(types);
    }

    void set_value(int value) {
        value_opt = value;
    }

    void set_value_gt(int value) {
        value_gt_opt = value;
    }

    void set_value_gte(int value) {
        value_gte_opt = value;
    }

    void set_value_lt(int value) {
        value_lt_opt = value;
    }

    void set_value_lte(int value) {
        value_lte_opt = value;
    }

    void set_state(TransactionState state) {
        state_opt = state;
    }

    void set_state_in(std::vector<TransactionState> states) {
        state_in_opt = std::move(states);
    }

    void set_wallet(std::string wallet) {
        wallet_opt = std::move(wallet);
    }

    void set_wallet_in(std::vector<std::string> wallets) {
        wallet_in_opt = std::move(wallets);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        JsonValue json = JsonValue::create_object();

        JsonUtils::try_set_field(json, "and", and_filters_opt);
        JsonUtils::try_set_field(json, "or", or_filters_opt);
        JsonUtils::try_set_field(json, "id", id_opt);
        JsonUtils::try_set_field(json, "id_in", id_in_opt);
        JsonUtils::try_set_field(json, "transactionId", transaction_id_opt);
        JsonUtils::try_set_field(json, "transactionId_in", transaction_id_in_opt);
        JsonUtils::try_set_field(json, "assetId", asset_id_opt);
        JsonUtils::try_set_field(json, "assetId_in", asset_id_in_opt);
        JsonUtils::try_set_field(json, "type", type_opt);
        JsonUtils::try_set_field(json, "type_in", type_in_opt);
        JsonUtils::try_set_field(json, "value", value_opt);
        JsonUtils::try_set_field(json, "value_gt", value_gt_opt);
        JsonUtils::try_set_field(json, "value_gte", value_gte_opt);
        JsonUtils::try_set_field(json, "value_lt", value_lt_opt);
        JsonUtils::try_set_field(json, "value_lte", value_lte_opt);
        JsonUtils::try_set_field(json, "state", state_opt);
        JsonUtils::try_set_field(json, "state_in", state_in_opt);
        JsonUtils::try_set_field(json, "wallet", wallet_opt);
        JsonUtils::try_set_field(json, "wallet_in", wallet_in_opt);

        return json;
    }

    bool operator==(const Impl& rhs) const {
        return and_filters_opt == rhs.and_filters_opt
               && or_filters_opt == rhs.or_filters_opt
               && id_opt == rhs.id_opt
               && id_in_opt == rhs.id_in_opt
               && transaction_id_opt == rhs.transaction_id_opt
               && transaction_id_in_opt == rhs.transaction_id_in_opt
               && asset_id_opt == rhs.asset_id_opt
               && asset_id_in_opt == rhs.asset_id_in_opt
               && type_opt == rhs.type_opt
               && type_in_opt == rhs.type_in_opt
               && value_opt == rhs.value_opt
               && value_gt_opt == rhs.value_gt_opt
               && value_gte_opt == rhs.value_gte_opt
               && value_lt_opt == rhs.value_lt_opt
               && value_lte_opt == rhs.value_lte_opt
               && state_opt == rhs.state_opt
               && state_in_opt == rhs.state_in_opt
               && wallet_opt == rhs.wallet_opt
               && wallet_in_opt == rhs.wallet_in_opt;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::vector<TransactionFilter>> and_filters_opt;
    std::optional<std::vector<TransactionFilter>> or_filters_opt;
    std::optional<std::string> id_opt;
    std::optional<std::vector<std::string>> id_in_opt;
    std::optional<std::string> transaction_id_opt;
    std::optional<std::vector<std::string>> transaction_id_in_opt;
    std::optional<std::string> asset_id_opt;
    std::optional<std::vector<std::string>> asset_id_in_opt;
    std::optional<TransactionType> type_opt;
    std::optional<std::vector<TransactionType>> type_in_opt;
    std::optional<int> value_opt;
    std::optional<int> value_gt_opt;
    std::optional<int> value_gte_opt;
    std::optional<int> value_lt_opt;
    std::optional<int> value_lte_opt;
    std::optional<TransactionState> state_opt;
    std::optional<std::vector<TransactionState>> state_in_opt;
    std::optional<std::string> wallet_opt;
    std::optional<std::vector<std::string>> wallet_in_opt;
};

TransactionFilter::TransactionFilter() : pimpl(std::make_unique<Impl>()) {
}

TransactionFilter::TransactionFilter(const TransactionFilter& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

TransactionFilter::TransactionFilter(TransactionFilter&& other) noexcept = default;

TransactionFilter::~TransactionFilter() = default;

std::string TransactionFilter::serialize() const {
    return pimpl->serialize();
}

TransactionFilter& TransactionFilter::set_and(std::vector<TransactionFilter> others) {
    pimpl->set_and(std::move(others));
    return *this;
}

TransactionFilter& TransactionFilter::set_or(std::vector<TransactionFilter> others) {
    pimpl->set_or(std::move(others));
    return *this;
}

TransactionFilter& TransactionFilter::set_id(std::string id) {
    pimpl->set_id(std::move(id));
    return *this;
}

TransactionFilter& TransactionFilter::set_id_in(std::vector<std::string> ids) {
    pimpl->set_id_in(std::move(ids));
    return *this;
}

TransactionFilter& TransactionFilter::set_transaction_id(std::string transaction_id) {
    pimpl->set_transaction_id(std::move(transaction_id));
    return *this;
}

TransactionFilter& TransactionFilter::set_transaction_id_in(std::vector<std::string> transaction_ids) {
    pimpl->set_transaction_id_in(std::move(transaction_ids));
    return *this;
}

TransactionFilter& TransactionFilter::set_asset_id(std::string asset_id) {
    pimpl->set_asset_id(std::move(asset_id));
    return *this;
}

TransactionFilter& TransactionFilter::set_asset_id_in(std::vector<std::string> asset_ids) {
    pimpl->set_asset_id_in(std::move(asset_ids));
    return *this;
}

TransactionFilter& TransactionFilter::set_type(TransactionType type) {
    pimpl->set_type(type);
    return *this;
}

TransactionFilter& TransactionFilter::set_type_in(std::vector<TransactionType> types) {
    pimpl->set_type_in(std::move(types));
    return *this;
}

TransactionFilter& TransactionFilter::set_value(int value) {
    pimpl->set_value(value);
    return *this;
}

TransactionFilter& TransactionFilter::set_value_gt(int value) {
    pimpl->set_value_gt(value);
    return *this;
}

TransactionFilter& TransactionFilter::set_value_gte(int value) {
    pimpl->set_value_gte(value);
    return *this;
}

TransactionFilter& TransactionFilter::set_value_lt(int value) {
    pimpl->set_value_lt(value);
    return *this;
}

TransactionFilter& TransactionFilter::set_value_lte(int value) {
    pimpl->set_value_lte(value);
    return *this;
}

TransactionFilter& TransactionFilter::set_state(TransactionState state) {
    pimpl->set_state(state);
    return *this;
}

TransactionFilter& TransactionFilter::set_state_in(std::vector<TransactionState> states) {
    pimpl->set_state_in(std::move(states));
    return *this;
}

TransactionFilter& TransactionFilter::set_wallet(std::string wallet) {
    pimpl->set_wallet(std::move(wallet));
    return *this;
}

TransactionFilter& TransactionFilter::set_wallet_in(std::vector<std::string> wallets) {
    pimpl->set_wallet_in(std::move(wallets));
    return *this;
}

JsonValue TransactionFilter::to_json() const {
    return pimpl->to_json();
}

bool TransactionFilter::operator==(const TransactionFilter& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool TransactionFilter::operator!=(const TransactionFilter& rhs) const {
    return *pimpl != *rhs.pimpl;
}

TransactionFilter& TransactionFilter::operator=(const TransactionFilter& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
