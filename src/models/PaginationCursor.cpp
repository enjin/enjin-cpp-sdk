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

#include "enjinsdk/models/PaginationCursor.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void PaginationCursor::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        total.reset();
        per_page.reset();
        current_page.reset();
        has_pages.reset();
        from.reset();
        to.reset();
        last_page.reset();
        has_more_pages.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "total", total);
    JsonUtils::try_get_field(json_object, "perPage", per_page);
    JsonUtils::try_get_field(json_object, "currentPage", current_page);
    JsonUtils::try_get_field(json_object, "hasPages", has_pages);
    JsonUtils::try_get_field(json_object, "from", from);
    JsonUtils::try_get_field(json_object, "to", to);
    JsonUtils::try_get_field(json_object, "lastPage", last_page);
    JsonUtils::try_get_field(json_object, "hasMorePages", has_more_pages);
}

const std::optional<int>& PaginationCursor::get_total() const {
    return total;
}

const std::optional<int>& PaginationCursor::get_per_page() const {
    return per_page;
}

const std::optional<int>& PaginationCursor::get_current_page() const {
    return current_page;
}

const std::optional<bool>& PaginationCursor::get_has_pages() const {
    return has_pages;
}

const std::optional<int>& PaginationCursor::get_from() const {
    return from;
}

const std::optional<int>& PaginationCursor::get_to() const {
    return to;
}

const std::optional<int>& PaginationCursor::get_last_page() const {
    return last_page;
}

const std::optional<bool>& PaginationCursor::get_has_more_pages() const {
    return has_more_pages;
}

bool PaginationCursor::operator==(const PaginationCursor& rhs) const {
    return total == rhs.total
           && per_page == rhs.per_page
           && current_page == rhs.current_page
           && has_pages == rhs.has_pages
           && from == rhs.from
           && to == rhs.to
           && last_page == rhs.last_page
           && has_more_pages == rhs.has_more_pages;
}

bool PaginationCursor::operator!=(const PaginationCursor& rhs) const {
    return !(*this == rhs);
}
