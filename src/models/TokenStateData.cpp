#include "enjinsdk/models/TokenStateData.hpp"
#include <string>

namespace enjin::sdk::models {

void TokenStateData::deserialize(const std::string& json) {

}

const std::optional<bool>& TokenStateData::get_nonfungible() const {
    return nonfungible;
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

}
