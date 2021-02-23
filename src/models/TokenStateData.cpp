#include "enjinsdk/models/TokenStateData.hpp"

#include "EnumUtils.hpp"
#include "rapidjson/document.h"

namespace enjin::sdk::models {

void TokenStateData::deserialize(const std::string& json) {
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
            supply_model.emplace(utils::deserialize_token_supply_model(document[SUPPLY_MODEL_KEY].GetString()));
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

const std::optional<bool>& TokenStateData::get_non_fungible() const {
    return non_fungible;
}

const std::optional<int>& TokenStateData::get_block_height() const {
    return block_height;
}

const std::optional<std::string>& TokenStateData::get_creator() const {
    return creator;
}

const std::optional<int>& TokenStateData::get_first_block() const {
    return first_block;
}

const std::optional<std::string>& TokenStateData::get_reserve() const {
    return reserve;
}

const std::optional<TokenSupplyModel>& TokenStateData::get_supply_model() const {
    return supply_model;
}

const std::optional<std::string>& TokenStateData::get_circulating_supply() const {
    return circulating_supply;
}

const std::optional<std::string>& TokenStateData::get_mintable_supply() const {
    return mintable_supply;
}

const std::optional<std::string>& TokenStateData::get_total_supply() const {
    return total_supply;
}

bool TokenStateData::operator==(const TokenStateData& rhs) const {
    return non_fungible == rhs.non_fungible &&
           block_height == rhs.block_height &&
           creator == rhs.creator &&
           first_block == rhs.first_block &&
           reserve == rhs.reserve &&
           supply_model == rhs.supply_model &&
           circulating_supply == rhs.circulating_supply &&
           mintable_supply == rhs.mintable_supply &&
           total_supply == rhs.total_supply;
}

bool TokenStateData::operator!=(const TokenStateData& rhs) const {
    return !(rhs == *this);
}

}
