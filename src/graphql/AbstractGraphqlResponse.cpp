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

#include "enjinsdk/internal/AbstractGraphqlResponse.hpp"

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::utils;

const std::optional<std::vector<GraphqlError>>& AbstractGraphqlResponse::get_errors() const {
    return errors;
}

bool AbstractGraphqlResponse::has_errors() const noexcept {
    return errors.has_value() && !errors.value().empty();
}

bool AbstractGraphqlResponse::is_successful() const noexcept {
    return !(is_empty() || has_errors());
}

void AbstractGraphqlResponse::process(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        return;
    }

    JsonUtils::try_get_field(json_object, "errors", errors);

    JsonValue data_object;

    if (json_object.try_get_object_field("data", data_object) && data_object.is_object()) {
        process_data(data_object);
    }
}
