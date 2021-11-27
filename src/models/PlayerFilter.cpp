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

#include "enjinsdk/models/PlayerFilter.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string PlayerFilter::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (and_filters.has_value()) {
        utils::set_array_member_from_type_vector<PlayerFilter>(document, AND_KEY, and_filters.value());
    }
    if (or_filters.has_value()) {
        utils::set_array_member_from_type_vector<PlayerFilter>(document, OR_KEY, or_filters.value());
    }
    if (id.has_value()) {
        utils::set_string_member(document, ID_KEY, id.value());
    }
    if (id_in.has_value()) {
        utils::set_array_member_from_string_vector(document, ID_IN_KEY, id_in.value());
    }

    return utils::document_to_string(document);
}

PlayerFilter& PlayerFilter::set_and(std::vector<PlayerFilter> others) {
    and_filters = std::move(others);
    return *this;
}

PlayerFilter& PlayerFilter::set_or(std::vector<PlayerFilter> others) {
    or_filters = std::move(others);
    return *this;
}

PlayerFilter& PlayerFilter::set_id(std::string id) {
    PlayerFilter::id = std::move(id);
    return *this;
}

PlayerFilter& PlayerFilter::set_id_in(std::vector<std::string> ids) {
    id_in = std::move(ids);
    return *this;
}

bool PlayerFilter::operator==(const PlayerFilter& rhs) const {
    return and_filters == rhs.and_filters &&
           or_filters == rhs.or_filters &&
           id == rhs.id &&
           id_in == rhs.id_in;
}

bool PlayerFilter::operator!=(const PlayerFilter& rhs) const {
    return !(rhs == *this);
}

}
