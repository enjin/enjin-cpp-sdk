#include "enjinsdk/models/SupplyModels.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void SupplyModels::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(FIXED_KEY) && document[FIXED_KEY].IsString()) {
            fixed.emplace(document[FIXED_KEY].GetString());
        }
        if (document.HasMember(SETTABLE_KEY) && document[SETTABLE_KEY].IsString()) {
            settable.emplace(document[SETTABLE_KEY].GetString());
        }
        if (document.HasMember(INFINITE_KEY) && document[INFINITE_KEY].IsString()) {
            infinite.emplace(document[INFINITE_KEY].GetString());
        }
        if (document.HasMember(COLLAPSING_KEY) && document[COLLAPSING_KEY].IsString()) {
            collapsing.emplace(document[COLLAPSING_KEY].GetString());
        }
        if (document.HasMember(ANNUAL_VALUE_KEY) && document[ANNUAL_VALUE_KEY].IsString()) {
            annual_value.emplace(document[ANNUAL_VALUE_KEY].GetString());
        }
        if (document.HasMember(ANNUAL_PERCENTAGE_KEY) && document[ANNUAL_PERCENTAGE_KEY].IsString()) {
            annual_percentage.emplace(document[ANNUAL_PERCENTAGE_KEY].GetString());
        }
    }
}

const std::optional<std::string>& SupplyModels::get_fixed() const {
    return fixed;
}

const std::optional<std::string>& SupplyModels::get_settable() const {
    return settable;
}

const std::optional<std::string>& SupplyModels::get_infinite() const {
    return infinite;
}

const std::optional<std::string>& SupplyModels::get_collapsing() const {
    return collapsing;
}

const std::optional<std::string>& SupplyModels::get_annual_value() const {
    return annual_value;
}

const std::optional<std::string>& SupplyModels::get_annual_percentage() const {
    return annual_percentage;
}

bool SupplyModels::operator==(const SupplyModels& rhs) const {
    return fixed == rhs.fixed &&
           settable == rhs.settable &&
           infinite == rhs.infinite &&
           collapsing == rhs.collapsing &&
           annual_value == rhs.annual_value &&
           annual_percentage == rhs.annual_percentage;
}

bool SupplyModels::operator!=(const SupplyModels& rhs) const {
    return !(rhs == *this);
}

}
