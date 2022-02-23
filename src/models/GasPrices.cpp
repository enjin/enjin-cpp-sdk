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

#include "enjinsdk/models/GasPrices.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void GasPrices::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(SAFE_LOW_KEY) && document[SAFE_LOW_KEY].IsNumber()) {
            safe_low.emplace(document[SAFE_LOW_KEY].GetFloat());
        }
        if (document.HasMember(AVERAGE_KEY) && document[AVERAGE_KEY].IsNumber()) {
            average.emplace(document[AVERAGE_KEY].GetFloat());
        }
        if (document.HasMember(FAST_KEY) && document[FAST_KEY].IsNumber()) {
            fast.emplace(document[FAST_KEY].GetFloat());
        }
        if (document.HasMember(FASTEST_KEY) && document[FASTEST_KEY].IsNumber()) {
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
