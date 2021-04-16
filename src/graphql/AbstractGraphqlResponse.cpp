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

#include "enjinsdk/internal/AbstractGraphqlResponse.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::graphql {

constexpr char DATA_KEY[] = "data";
constexpr char ERROR_KEY[] = "error";
constexpr char ERRORS_KEY[] = "errors";

const std::optional<std::vector<GraphqlError>>& AbstractGraphqlResponse::get_errors() const {
    return errors;
}

const std::optional<enjin::sdk::models::PaginationCursor>& AbstractGraphqlResponse::get_cursor() const {
    return cursor;
}

bool AbstractGraphqlResponse::has_errors() const noexcept {
    return errors.has_value() && !errors.value().empty();
}

bool AbstractGraphqlResponse::is_successful() const noexcept {
    return !(is_empty() || has_errors());
}

bool AbstractGraphqlResponse::is_paginated() const noexcept {
    return cursor.has_value();
}

void AbstractGraphqlResponse::process(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(DATA_KEY) && document[DATA_KEY].IsObject()) {
            process_data(utils::get_object_as_string(document, DATA_KEY));
        } else if (document.HasMember(ERROR_KEY) && document[ERROR_KEY].IsObject()) {
            process_errors(utils::get_object_as_string(document, ERROR_KEY));
        }
    }
}

void AbstractGraphqlResponse::process_errors(const std::string& error_json) {
    rapidjson::Document document;
    document.Parse(error_json.c_str());

    if (document.IsObject() && document.HasMember(ERRORS_KEY) && document[ERRORS_KEY].IsArray()) {
        errors.emplace(utils::get_array_as_type_vector<GraphqlError>(document, ERRORS_KEY));
    }
}

}
