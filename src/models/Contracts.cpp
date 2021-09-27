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

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Contracts::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ENJ_KEY) && document[ENJ_KEY].IsString()) {
            enj.emplace(document[ENJ_KEY].GetString());
        }
        if (document.HasMember(CRYPTO_ITEMS_KEY) && document[CRYPTO_ITEMS_KEY].IsString()) {
            crypto_items.emplace(document[CRYPTO_ITEMS_KEY].GetString());
        }
        if (document.HasMember(PLATFORM_REGISTRY_KEY) && document[PLATFORM_REGISTRY_KEY].IsString()) {
            platform_registry.emplace(document[PLATFORM_REGISTRY_KEY].GetString());
        }
        if (document.HasMember(SUPPLY_MODELS_KEY) && document[SUPPLY_MODELS_KEY].IsObject()) {
            supply_models.emplace(utils::get_object_as_type<SupplyModels>(document, SUPPLY_MODELS_KEY));
        }
    }
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
    return enj == rhs.enj &&
           crypto_items == rhs.crypto_items &&
           platform_registry == rhs.platform_registry &&
           supply_models == rhs.supply_models;
}

bool Contracts::operator!=(const Contracts& rhs) const {
    return !(rhs == *this);
}

}
