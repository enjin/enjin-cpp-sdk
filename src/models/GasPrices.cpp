#include "enjinsdk/models/GasPrices.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void GasPrices::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(SAFE_LOW_KEY) && document[SAFE_LOW_KEY].IsFloat()) {
            safe_low.emplace(document[SAFE_LOW_KEY].GetFloat());
        }
        if (document.HasMember(AVERAGE_KEY) && document[AVERAGE_KEY].IsFloat()) {
            average.emplace(document[AVERAGE_KEY].GetFloat());
        }
        if (document.HasMember(FAST_KEY) && document[FAST_KEY].IsFloat()) {
            fast.emplace(document[FAST_KEY].GetFloat());
        }
        if (document.HasMember(FASTEST_KEY) && document[FASTEST_KEY].IsFloat()) {
            fastest.emplace(document[FASTEST_KEY].GetFloat());
        }
    }
}

const std::optional<float>& GasPrices::get_safe_low() const {
    return safe_low;
}

const std::optional<float>& GasPrices::get_average() const {
    return average;
}

const std::optional<float>& GasPrices::get_fast() const {
    return fast;
}

const std::optional<float>& GasPrices::get_fastest() const {
    return fastest;
}

bool GasPrices::operator==(const GasPrices& rhs) const {
    return safe_low == rhs.safe_low &&
           average == rhs.average &&
           fast == rhs.fast &&
           fastest == rhs.fastest;
}

bool GasPrices::operator!=(const GasPrices& rhs) const {
    return !(rhs == *this);
}

}
