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

#include "enjinsdk/models/PaginationOptions.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string PaginationOptions::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (page.has_value()) {
        utils::set_integer_member(document, PAGE_KEY, page.value());
    }
    if (limit.has_value()) {
        utils::set_integer_member(document, LIMIT_KEY, limit.value());
    }

    return utils::document_to_string(document);
}

PaginationOptions& PaginationOptions::set_page(int page) {
    PaginationOptions::page = page;
    return *this;
}

PaginationOptions& PaginationOptions::set_limit(int limit) {
    PaginationOptions::limit = limit;
    return *this;
}

bool PaginationOptions::operator==(const PaginationOptions& rhs) const {
    return page == rhs.page &&
           limit == rhs.limit;
}

bool PaginationOptions::operator!=(const PaginationOptions& rhs) const {
    return !(rhs == *this);
}

}
