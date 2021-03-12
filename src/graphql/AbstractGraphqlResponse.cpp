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

bool AbstractGraphqlResponse::has_errors() noexcept {
    return errors.has_value() && !errors.value().empty();
}

bool AbstractGraphqlResponse::is_successful() noexcept {
    return !(is_empty() || has_errors());
}

bool AbstractGraphqlResponse::is_paginated() noexcept {
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
