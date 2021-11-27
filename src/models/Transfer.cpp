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

#include "enjinsdk/models/Transfer.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string Transfer::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (from.has_value()) {
        utils::set_string_member(document, FROM_KEY, from.value());
    }
    if (to.has_value()) {
        utils::set_string_member(document, TO_KEY, to.value());
    }
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

Transfer& Transfer::set_from(std::string address) {
    from = std::move(address);
    return *this;
}

Transfer& Transfer::set_to(std::string address) {
    to = std::move(address);
    return *this;
}

Transfer& Transfer::set_asset_id(std::string id) {
    asset_id = std::move(id);
    return *this;
}

Transfer& Transfer::set_asset_index(std::string index) {
    asset_index = std::move(index);
    return *this;
}

Transfer& Transfer::set_value(std::string value) {
    Transfer::value = std::move(value);
    return *this;
}

bool Transfer::operator==(const Transfer& rhs) const {
    return from == rhs.from &&
           to == rhs.to &&
           asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           value == rhs.value;
}

bool Transfer::operator!=(const Transfer& rhs) const {
    return !(rhs == *this);
}

}
