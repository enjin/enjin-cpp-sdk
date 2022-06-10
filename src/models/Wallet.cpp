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

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Wallet::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            eth_address.reset();
            enj_allowance.reset();
            enj_balance.reset();
            eth_balance.reset();
            assets_created.reset();
            balances.reset();
            transactions.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "ethAddress", eth_address);
        JsonUtils::try_get_field(json_object, "enjAllowance", enj_allowance);
        JsonUtils::try_get_field(json_object, "enjBalance", enj_balance);
        JsonUtils::try_get_field(json_object, "ethBalance", eth_balance);
        JsonUtils::try_get_field(json_object, "assetsCreated", assets_created);
        JsonUtils::try_get_field(json_object, "balances", balances);
        JsonUtils::try_get_field(json_object, "transactions", transactions);
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

    [[nodiscard]] const std::optional<std::vector<Transaction>>& get_transactions() const {
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
    std::optional<std::vector<Transaction>> transactions;
};

Wallet::Wallet() : pimpl(std::make_unique<Impl>()) {
}

Wallet::Wallet(const Wallet& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

Wallet::Wallet(Wallet&& other) noexcept = default;

Wallet::~Wallet() = default;

void Wallet::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& Wallet::get_eth_address() const {
    return pimpl->get_eth_address();
}

const std::optional<float>& Wallet::get_enj_allowance() const {
    return pimpl->get_enj_allowance();
}

const std::optional<float>& Wallet::get_enj_balance() const {
    return pimpl->get_enj_balance();
}

const std::optional<float>& Wallet::get_eth_balance() const {
    return pimpl->get_eth_balance();
}

const std::optional<std::vector<Asset>>& Wallet::get_assets_created() const {
    return pimpl->get_assets_created();
}

const std::optional<std::vector<Balance>>& Wallet::get_balances() const {
    return pimpl->get_balances();
}

const std::optional<std::vector<Transaction>>& Wallet::get_transactions() const {
    return pimpl->get_transactions();
}

bool Wallet::operator==(const Wallet& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool Wallet::operator!=(const Wallet& rhs) const {
    return *pimpl != *rhs.pimpl;
}

Wallet& enjin::sdk::models::Wallet::operator=(const Wallet& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
