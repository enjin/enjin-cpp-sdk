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

#include "enjinsdk/models/Wallet.hpp"

#include "RapidJsonUtils.hpp"

using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Wallet::Impl : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        rapidjson::Document document;
        document.Parse(json.c_str());

        if (!document.IsObject()) {
            return;
        }

        if (document.HasMember(ETH_ADDRESS_KEY) && document[ETH_ADDRESS_KEY].IsString()) {
            eth_address.emplace(document[ETH_ADDRESS_KEY].GetString());
        }

        if (document.HasMember(ENJ_ALLOWANCE_KEY) && document[ENJ_ALLOWANCE_KEY].IsFloat()) {
            enj_allowance.emplace(document[ENJ_ALLOWANCE_KEY].GetFloat());
        }

        if (document.HasMember(ENJ_BALANCE_KEY) && document[ENJ_BALANCE_KEY].IsFloat()) {
            enj_balance.emplace(document[ENJ_BALANCE_KEY].GetFloat());
        }

        if (document.HasMember(ETH_BALANCE_KEY) && document[ETH_BALANCE_KEY].IsFloat()) {
            eth_balance.emplace(document[ETH_BALANCE_KEY].GetFloat());
        }

        if (document.HasMember(ASSETS_CREATED_KEY) && document[ASSETS_CREATED_KEY].IsArray()) {
            assets_created.emplace(get_array_as_type_vector<Asset>(document, ASSETS_CREATED_KEY));
        }

        if (document.HasMember(BALANCES_KEY) && document[BALANCES_KEY].IsArray()) {
            balances.emplace(get_array_as_type_vector<Balance>(document, BALANCES_KEY));
        }

        if (document.HasMember(TRANSACTIONS_KEY) && document[TRANSACTIONS_KEY].IsArray()) {
            transactions.emplace(get_array_as_type_vector<Request>(document, TRANSACTIONS_KEY));
        }
    }

    [[nodiscard]] const std::optional<std::string>& get_eth_address() const {
        return eth_address;
    }

    [[nodiscard]] const std::optional<float>& get_enj_allowance() const {
        return enj_allowance;
    }

    [[nodiscard]] const std::optional<float>& get_enj_balance() const {
        return enj_balance;
    }

    [[nodiscard]] const std::optional<float>& get_eth_balance() const {
        return eth_balance;
    }

    [[nodiscard]] const std::optional<std::vector<Asset>>& get_assets_created() const {
        return assets_created;
    }

    [[nodiscard]] const std::optional<std::vector<Balance>>& get_balances() const {
        return balances;
    }

    [[nodiscard]] const std::optional<std::vector<Request>>& get_transactions() const {
        return transactions;
    }

    bool operator==(const Impl& rhs) const {
        return eth_address == rhs.eth_address
               && enj_allowance == rhs.enj_allowance
               && enj_balance == rhs.enj_balance
               && eth_balance == rhs.eth_balance
               && assets_created == rhs.assets_created
               && balances == rhs.balances
               && transactions == rhs.transactions;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> eth_address;
    std::optional<float> enj_allowance;
    std::optional<float> enj_balance;
    std::optional<float> eth_balance;
    std::optional<std::vector<Asset>> assets_created;
    std::optional<std::vector<Balance>> balances;
    std::optional<std::vector<Request>> transactions;

    constexpr static char ETH_ADDRESS_KEY[] = "ethAddress";
    constexpr static char ENJ_ALLOWANCE_KEY[] = "enjAllowance";
    constexpr static char ENJ_BALANCE_KEY[] = "enjBalance";
    constexpr static char ETH_BALANCE_KEY[] = "ethBalance";
    constexpr static char ASSETS_CREATED_KEY[] = "assetsCreated";
    constexpr static char BALANCES_KEY[] = "balances";
    constexpr static char TRANSACTIONS_KEY[] = "transactions";
};

Wallet::Wallet() : impl(std::make_unique<Impl>()) {
}

Wallet::Wallet(const Wallet& other) {
    impl = std::make_unique<Impl>(*other.impl);
}

Wallet::Wallet(Wallet&& other) noexcept = default;

Wallet::~Wallet() = default;

void Wallet::deserialize(const std::string& json) {
    impl->deserialize(json);
}

const std::optional<std::string>& Wallet::get_eth_address() const {
    return impl->get_eth_address();
}

const std::optional<float>& Wallet::get_enj_allowance() const {
    return impl->get_enj_allowance();
}

const std::optional<float>& Wallet::get_enj_balance() const {
    return impl->get_enj_balance();
}

const std::optional<float>& Wallet::get_eth_balance() const {
    return impl->get_eth_balance();
}

const std::optional<std::vector<Asset>>& Wallet::get_assets_created() const {
    return impl->get_assets_created();
}

const std::optional<std::vector<Balance>>& Wallet::get_balances() const {
    return impl->get_balances();
}

const std::optional<std::vector<Request>>& Wallet::get_transactions() const {
    return impl->get_transactions();
}

bool Wallet::operator==(const Wallet& rhs) const {
    return *impl == *rhs.impl;
}

bool Wallet::operator!=(const Wallet& rhs) const {
    return !(*this == rhs);
}
