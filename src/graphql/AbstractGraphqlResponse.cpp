#include "enjinsdk/internal/AbstractGraphqlResponse.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace enjin::sdk::graphql {

std::optional<std::vector<GraphqlError>> AbstractGraphqlResponse::get_errors() {
    return errors;
}

std::optional<enjin::sdk::models::PaginationCursor> AbstractGraphqlResponse::get_cursor() {
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

void AbstractGraphqlResponse::process(const char* json) {
    rapidjson::Document document;
    document.Parse(json);
    if (document.IsObject()) {
        if (document.HasMember(DATA_KEY) && document[DATA_KEY].IsObject()) {
            auto& data_obj = document[DATA_KEY];
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            data_obj.Accept(writer);
            const char* data_json = buffer.GetString();
            process_data(data_json);
        } else if (document.HasMember(ERROR_KEY) && document[ERROR_KEY].IsObject()) {
            auto& error_obj = document[ERROR_KEY];
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            error_obj.Accept(writer);
            const char* error_json = buffer.GetString();
            process_errors(error_json);
        }
    }
}

void AbstractGraphqlResponse::process_errors(const char* error_json) {
    rapidjson::Document document;
    document.Parse(error_json);
    if (!document.IsObject() || !document.HasMember(ERRORS_KEY) && document[ERRORS_KEY].IsArray()) {
        return;
    }

    std::vector<GraphqlError> list;
    for (auto& v : document[ERRORS_KEY].GetArray()) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        v.Accept(writer);
        const char* v_json = buffer.GetString();

        GraphqlError error;
        error.deserialize(v_json);
        list.push_back(error);
    }
    errors.emplace(list);
}

}
