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

#include "enjinsdk/models/MintInput.hpp"

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

std::string MintInput::serialize() const {
    return to_json().to_string();
}

MintInput& MintInput::set_to(std::string address) {
    to_opt = std::move(address);
    return *this;
}

MintInput& MintInput::set_value(std::string value) {
    value_opt = std::move(value);
    return *this;
}

JsonValue MintInput::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::try_set_field(json, "to", to_opt);
    JsonUtils::try_set_field(json, "value", value_opt);

    return json;
}

bool MintInput::operator==(const MintInput& rhs) const {
    return to_opt == rhs.to_opt
           && value_opt == rhs.value_opt;
}

bool MintInput::operator!=(const MintInput& rhs) const {
    return !(*this == rhs);
}
