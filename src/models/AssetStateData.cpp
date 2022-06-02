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

#include "enjinsdk/models/AssetStateData.hpp"

#include "RapidJsonUtils.hpp"
#include "enjinsdk/EnumUtils.hpp"

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void AssetStateData::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());

    if (document.IsObject()) {
        if (document.HasMember(NONFUNGIBLE_KEY) && document[NONFUNGIBLE_KEY].IsBool()) {
            non_fungible.emplace(document[NONFUNGIBLE_KEY].GetBool());
        }

        if (document.HasMember(BLOCK_HEIGHT_KEY) && document[BLOCK_HEIGHT_KEY].IsInt()) {
            block_height.emplace(document[BLOCK_HEIGHT_KEY].GetInt());
        }

        if (document.HasMember(CREATOR_KEY) && document[CREATOR_KEY].IsString()) {
            creator.emplace(document[CREATOR_KEY].GetString());
        }

        if (document.HasMember(FIRST_BLOCK_KEY) && document[FIRST_BLOCK_KEY].IsInt()) {
            first_block.emplace(document[FIRST_BLOCK_KEY].GetInt());
        }

        if (document.HasMember(RESERVE_KEY) && document[RESERVE_KEY].IsString()) {
            reserve.emplace(document[RESERVE_KEY].GetString());
        }

        if (document.HasMember(SUPPLY_MODEL_KEY) && document[SUPPLY_MODEL_KEY].IsString()) {
            supply_model.emplace(EnumUtils::deserialize_asset_supply_model(document[SUPPLY_MODEL_KEY].GetString()));
        }

        if (document.HasMember(CIRCULATING_SUPPLY_KEY) && document[CIRCULATING_SUPPLY_KEY].IsString()) {
            circulating_supply.emplace(document[CIRCULATING_SUPPLY_KEY].GetString());
        }

        if (document.HasMember(MINTABLE_SUPPLY_KEY) && document[MINTABLE_SUPPLY_KEY].IsString()) {
            mintable_supply.emplace(document[MINTABLE_SUPPLY_KEY].GetString());
        }

        if (document.HasMember(TOTAL_SUPPLY_KEY) && document[TOTAL_SUPPLY_KEY].IsString()) {
            total_supply.emplace(document[TOTAL_SUPPLY_KEY].GetString());
        }
    }
}

const std::optional<bool>& AssetStateData::get_non_fungible() const {
    return non_fungible;
}

const std::optional<int>& AssetStateData::get_block_height() const {
    return block_height;
}

const std::optional<std::string>& AssetStateData::get_creator() const {
    return creator;
}

const std::optional<int>& AssetStateData::get_first_block() const {
    return first_block;
}

const std::optional<std::string>& AssetStateData::get_reserve() const {
    return reserve;
}

const std::optional<AssetSupplyModel>& AssetStateData::get_supply_model() const {
    return supply_model;
}

const std::optional<std::string>& AssetStateData::get_circulating_supply() const {
    return circulating_supply;
}

const std::optional<std::string>& AssetStateData::get_mintable_supply() const {
    return mintable_supply;
}

const std::optional<std::string>& AssetStateData::get_total_supply() const {
    return total_supply;
}

bool AssetStateData::operator==(const AssetStateData& rhs) const {
    return non_fungible == rhs.non_fungible
           && block_height == rhs.block_height
           && creator == rhs.creator
           && first_block == rhs.first_block
           && reserve == rhs.reserve
           && supply_model == rhs.supply_model
           && circulating_supply == rhs.circulating_supply
           && mintable_supply == rhs.mintable_supply
           && total_supply == rhs.total_supply;
}

bool AssetStateData::operator!=(const AssetStateData& rhs) const {
    return !(rhs == *this);
}
