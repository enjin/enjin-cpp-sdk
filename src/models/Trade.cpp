/* Copyright 2021 Enjin Pte Ltd.
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

#include "enjinsdk/models/Trade.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string Trade::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (asset_id.has_value()) {
        utils::set_string_member(document, ASSET_ID_KEY, asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, ASSET_INDEX_KEY, asset_index.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, VALUE_KEY, value.value());
    }

    return utils::document_to_string(document);
}

Trade& Trade::set_asset_id(const std::string& id) {
    asset_id = id;
    return *this;
}

Trade& Trade::set_asset_index(const std::string& index) {
    asset_index = index;
    return *this;
}

Trade& Trade::set_value(const std::string& value) {
    Trade::value = value;
    return *this;
}

bool Trade::operator==(const Trade& rhs) const {
    return asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           value == rhs.value;
}

bool Trade::operator!=(const Trade& rhs) const {
    return !(rhs == *this);
}

}
