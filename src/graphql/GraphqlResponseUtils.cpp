#include "enjinsdk/internal/GraphqlResponseUtils.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::graphql {

constexpr char RESULT_KEY[] = "result";
constexpr char ITEMS_KEY[] = "items";
constexpr char CURSOR_KEY[] = "cursor";

std::optional<bool> get_bool_result(const std::string& data_json) {
    rapidjson::Document document;
    document.Parse(data_json.c_str());

    if (document.IsObject() && document.HasMember(RESULT_KEY) && document[RESULT_KEY].IsBool()) {
        return document[RESULT_KEY].GetBool();
    }

    return std::nullopt;
}

std::optional<std::pair<models::PaginationCursor, std::vector<std::string>>>
get_pagination_data(const std::string& data_json) {
    rapidjson::Document document;
    document.Parse(data_json.c_str());

    if (!document.IsObject() || !document.HasMember(RESULT_KEY)) {
        return std::nullopt;
    }

    models::PaginationCursor cursor;
    std::vector<std::string> items;

    std::string result_json = utils::get_object_as_string(document, RESULT_KEY);
    rapidjson::Document result_document;
    result_document.Parse(result_json.c_str());
    auto result_obj = document[RESULT_KEY].GetObject();

    if (result_obj.HasMember(CURSOR_KEY) && result_obj[CURSOR_KEY].IsObject()) {
        cursor = utils::get_object_as_type<models::PaginationCursor>(result_document, CURSOR_KEY);
    }
    if (result_obj.HasMember(ITEMS_KEY) && result_obj[ITEMS_KEY].IsArray()) {
        items = utils::get_array_as_serialized_vector(result_document, ITEMS_KEY);
    }

    return std::make_pair(cursor, items);
}

std::optional<std::vector<std::string>> get_serialized_object_array(const std::string& data_json) {
    rapidjson::Document document;
    document.Parse(data_json.c_str());

    if (document.IsObject() && document.HasMember(RESULT_KEY) && document[RESULT_KEY].IsArray()) {
        return utils::get_array_as_serialized_vector(document, RESULT_KEY);
    }

    return std::nullopt;
}

std::optional<std::string> get_serialized_result_object(const std::string& data_json) {
    rapidjson::Document document;
    document.Parse(data_json.c_str());

    if (document.IsObject() && document.HasMember(RESULT_KEY) && document[RESULT_KEY].IsObject()) {
        return utils::get_object_as_string(document, RESULT_KEY);
    }

    return std::nullopt;
}

bool is_json_paginated(const std::string& data_json) {
    rapidjson::Document document;
    document.Parse(data_json.c_str());

    if (document.IsObject() && document.HasMember(RESULT_KEY) && document[RESULT_KEY].IsObject()) {
        auto result_obj = document[RESULT_KEY].GetObject();
        return result_obj.HasMember(CURSOR_KEY) && result_obj[CURSOR_KEY].IsObject();
    }

    return false;
}

}
