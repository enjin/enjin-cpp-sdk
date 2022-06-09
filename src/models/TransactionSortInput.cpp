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

#include "enjinsdk/models/TransactionSortInput.hpp"

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

std::string TransactionSortInput::serialize() const {
    return to_json().to_string();
}

TransactionSortInput& TransactionSortInput::set_field(TransactionField field) {
    field_opt = field;
    return *this;
}

TransactionSortInput& TransactionSortInput::set_direction(SortDirection direction) {
    direction_opt = direction;
    return *this;
}

JsonValue TransactionSortInput::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::try_set_field(json, "field", field_opt);
    JsonUtils::try_set_field(json, "direction", direction_opt);

    return json;
}

bool TransactionSortInput::operator==(const TransactionSortInput& rhs) const {
    return field_opt == rhs.field_opt
           && direction_opt == rhs.direction_opt;
}

bool TransactionSortInput::operator!=(const TransactionSortInput& rhs) const {
    return !(*this == rhs);
}
