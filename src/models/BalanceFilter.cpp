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
#include <utility>

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class BalanceFilter::Impl final : public ISerializable {
public:
    Impl() = default;

    ~Impl() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    void set_and(std::vector<BalanceFilter> others) {
        and_filters_opt = std::move(others);
    }

    void set_or(std::vector<BalanceFilter> others) {
        or_filters_opt = std::move(others);
    }

    void set_asset_id(std::string asset_id) {
        asset_id_opt = std::move(asset_id);
    }

    void set_asset_id_in(std::vector<std::string> asset_ids) {
        asset_id_in_opt = std::move(asset_ids);
    }

    void set_wallet(std::string wallet) {
        wallet_opt = std::move(wallet);
    }

    void set_wallet_in(std::vector<std::string> wallets) {
        wallet_in_opt = std::move(wallets);
    }

    void set_value(int value) {
        value_opt = value;
    }

    void set_value_is(Operator value_is) {
        value_is_opt = value_is;
    }

    [[nodiscard]] json::JsonValue to_json() const override {
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

    bool operator==(const Impl& rhs) const {
        return and_filters_opt == rhs.and_filters_opt
               && or_filters_opt == rhs.or_filters_opt
               && asset_id_opt == rhs.asset_id_opt
               && asset_id_in_opt == rhs.asset_id_in_opt
               && wallet_opt == rhs.wallet_opt
               && wallet_in_opt == rhs.wallet_in_opt
               && value_opt == rhs.value_opt
               && value_is_opt == rhs.value_is_opt;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::vector<BalanceFilter>> and_filters_opt;
    std::optional<std::vector<BalanceFilter>> or_filters_opt;
    std::optional<std::string> asset_id_opt;
    std::optional<std::vector<std::string>> asset_id_in_opt;
    std::optional<std::string> wallet_opt;
    std::optional<std::vector<std::string>> wallet_in_opt;
    std::optional<int> value_opt;
    std::optional<Operator> value_is_opt;
};

BalanceFilter::BalanceFilter() : pimpl(std::make_unique<Impl>()) {
}

BalanceFilter::BalanceFilter(const BalanceFilter& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

BalanceFilter::BalanceFilter(BalanceFilter&& other) noexcept = default;

BalanceFilter::~BalanceFilter() = default;

std::string BalanceFilter::serialize() const {
    return pimpl->serialize();
}

BalanceFilter& BalanceFilter::set_and(std::vector<BalanceFilter> others) {
    pimpl->set_and(std::move(others));
    return *this;
}

BalanceFilter& BalanceFilter::set_or(std::vector<BalanceFilter> others) {
    pimpl->set_or(std::move(others));
    return *this;
}

BalanceFilter& BalanceFilter::set_asset_id(std::string asset_id) {
    pimpl->set_asset_id(std::move(asset_id));
    return *this;
}

BalanceFilter& BalanceFilter::set_asset_id_in(std::vector<std::string> asset_ids) {
    pimpl->set_asset_id_in(std::move(asset_ids));
    return *this;
}

BalanceFilter& BalanceFilter::set_wallet(std::string wallet) {
    pimpl->set_wallet(std::move(wallet));
    return *this;
}

BalanceFilter& BalanceFilter::set_wallet_in(std::vector<std::string> wallets) {
    pimpl->set_wallet_in(std::move(wallets));
    return *this;
}

BalanceFilter& BalanceFilter::set_value(int value) {
    pimpl->set_value(value);
    return *this;
}

BalanceFilter& BalanceFilter::set_value_is(Operator value_is) {
    pimpl->set_value_is(value_is);
    return *this;
}

JsonValue BalanceFilter::to_json() const {
    return pimpl->to_json();
}

bool BalanceFilter::operator==(const BalanceFilter& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool BalanceFilter::operator!=(const BalanceFilter& rhs) const {
    return *pimpl != *rhs.pimpl;
}

BalanceFilter& BalanceFilter::operator=(const BalanceFilter& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
