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

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void GasPrices::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        safe_low.reset();
        average.reset();
        fast.reset();
        fastest.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "safeLow", safe_low);
    JsonUtils::try_get_field(json_object, "average", average);
    JsonUtils::try_get_field(json_object, "fast", fast);
    JsonUtils::try_get_field(json_object, "fastest", fastest);
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
    return safe_low == rhs.safe_low
           && average == rhs.average
           && fast == rhs.fast
           && fastest == rhs.fastest;
}

bool GasPrices::operator!=(const GasPrices& rhs) const {
    return !(*this == rhs);
}
