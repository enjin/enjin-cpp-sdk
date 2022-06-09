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

#include "enjinsdk/models/SupplyModels.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void SupplyModels::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        fixed.reset();
        settable.reset();
        infinite.reset();
        collapsing.reset();
        annual_value.reset();
        annual_percentage.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "fixed", fixed);
    JsonUtils::try_get_field(json_object, "settable", settable);
    JsonUtils::try_get_field(json_object, "infinite", infinite);
    JsonUtils::try_get_field(json_object, "collapsing", collapsing);
    JsonUtils::try_get_field(json_object, "annualValue", annual_value);
    JsonUtils::try_get_field(json_object, "annualPercentage", annual_percentage);
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
    return fixed == rhs.fixed
           && settable == rhs.settable
           && infinite == rhs.infinite
           && collapsing == rhs.collapsing
           && annual_value == rhs.annual_value
           && annual_percentage == rhs.annual_percentage;
}

bool SupplyModels::operator!=(const SupplyModels& rhs) const {
    return !(*this == rhs);
}
