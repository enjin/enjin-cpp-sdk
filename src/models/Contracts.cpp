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
using namespace enjin::sdk::utils;

void Contracts::deserialize(const std::string& json) {
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

const std::optional<std::string>& Contracts::get_enj() const {
    return enj;
}

const std::optional<std::string>& Contracts::get_crypto_items() const {
    return crypto_items;
}

const std::optional<std::string>& Contracts::get_platform_registry() const {
    return platform_registry;
}

const std::optional<SupplyModels>& Contracts::get_supply_models() const {
    return supply_models;
}

bool Contracts::operator==(const Contracts& rhs) const {
    return enj == rhs.enj
           && crypto_items == rhs.crypto_items
           && platform_registry == rhs.platform_registry
           && supply_models == rhs.supply_models;
}

bool Contracts::operator!=(const Contracts& rhs) const {
    return !(*this == rhs);
}
