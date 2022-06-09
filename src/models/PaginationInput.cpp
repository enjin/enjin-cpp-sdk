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

#include "enjinsdk/models/PaginationInput.hpp"

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

std::string PaginationInput::serialize() const {
    return to_json().to_string();
}

PaginationInput& PaginationInput::set_page(int page) {
    page_opt = page;
    return *this;
}

PaginationInput& PaginationInput::set_limit(int limit) {
    limit_opt = limit;
    return *this;
}

JsonValue PaginationInput::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::try_set_field(json, "page", page_opt);
    JsonUtils::try_set_field(json, "limit", limit_opt);

    return json;
}

bool PaginationInput::operator==(const PaginationInput& rhs) const {
    return page_opt == rhs.page_opt
           && limit_opt == rhs.limit_opt;
}

bool PaginationInput::operator!=(const PaginationInput& rhs) const {
    return !(*this == rhs);
}
