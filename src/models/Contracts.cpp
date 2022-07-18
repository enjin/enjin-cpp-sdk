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

#include "enjinsdk/models/Contracts.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Contracts::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            enj.reset();
            crypto_items.reset();
            platform_registry.reset();
            supply_models.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "enj", enj);
        JsonUtils::try_get_field(json_object, "cryptoItems", crypto_items);
        JsonUtils::try_get_field(json_object, "platformRegistry", platform_registry);
        JsonUtils::try_get_field(json_object, "supplyModels", supply_models);
    }

    [[nodiscard]] const std::optional<std::string>& get_enj() const {
        return enj;
    }

    [[nodiscard]] const std::optional<std::string>& get_crypto_items() const {
        return crypto_items;
    }

    [[nodiscard]] const std::optional<std::string>& get_platform_registry() const {
        return platform_registry;
    }

    [[nodiscard]] const std::optional<SupplyModels>& get_supply_models() const {
        return supply_models;
    }

    bool operator==(const Impl& rhs) const {
        return enj == rhs.enj
               && crypto_items == rhs.crypto_items
               && platform_registry == rhs.platform_registry
               && supply_models == rhs.supply_models;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> enj;
    std::optional<std::string> crypto_items;
    std::optional<std::string> platform_registry;
    std::optional<SupplyModels> supply_models;
};

Contracts::Contracts() : pimpl(std::make_unique<Impl>()) {
}

Contracts::Contracts(const Contracts& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

Contracts::Contracts(Contracts&& other) noexcept = default;

Contracts::~Contracts() = default;

void Contracts::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& Contracts::get_enj() const {
    return pimpl->get_enj();
}

const std::optional<std::string>& Contracts::get_crypto_items() const {
    return pimpl->get_crypto_items();
}

const std::optional<std::string>& Contracts::get_platform_registry() const {
    return pimpl->get_platform_registry();
}

const std::optional<SupplyModels>& Contracts::get_supply_models() const {
    return pimpl->get_supply_models();
}

bool Contracts::operator==(const Contracts& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool Contracts::operator!=(const Contracts& rhs) const {
    return *pimpl != *rhs.pimpl;
}

Contracts& Contracts::operator=(const Contracts& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
