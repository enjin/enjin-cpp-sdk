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

#include "enjinsdk/models/TransactionSort.hpp"

#include "RapidJsonUtils.hpp"
#include "enjinsdk/EnumUtils.hpp"

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

std::string TransactionSort::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (field.has_value()) {
        set_string_member(document, FIELD_KEY, EnumUtils::serialize_transaction_field(field.value()));
    }

    if (direction.has_value()) {
        set_string_member(document, DIRECTION_KEY, EnumUtils::serialize_sort_direction(direction.value()));
    }

    return document_to_string(document);
}

TransactionSort& TransactionSort::set_field(TransactionField field) {
    TransactionSort::field = field;
    return *this;
}

TransactionSort& TransactionSort::set_direction(SortDirection direction) {
    TransactionSort::direction = direction;
    return *this;
}

bool TransactionSort::operator==(const TransactionSort& rhs) const {
    return field == rhs.field
           && direction == rhs.direction;
}

bool TransactionSort::operator!=(const TransactionSort& rhs) const {
    return !(rhs == *this);
}
