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

#include "enjinsdk/models/AssetSort.hpp"

#include "RapidJsonUtils.hpp"
#include "enjinsdk/EnumUtils.hpp"

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

std::string AssetSort::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (field.has_value()) {
        set_string_member(document, FIELD_KEY, EnumUtils::serialize_asset_field(field.value()));
    }

    if (direction.has_value()) {
        set_string_member(document, DIRECTION_KEY, EnumUtils::serialize_sort_direction(direction.value()));
    }

    return document_to_string(document);
}

AssetSort& AssetSort::set_field(AssetField field) {
    AssetSort::field = field;
    return *this;
}

AssetSort& AssetSort::set_direction(SortDirection direction) {
    AssetSort::direction = direction;
    return *this;
}

bool AssetSort::operator==(const AssetSort& rhs) const {
    return field == rhs.field
           && direction == rhs.direction;
}

bool AssetSort::operator!=(const AssetSort& rhs) const {
    return !(rhs == *this);
}
