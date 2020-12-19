#ifndef ENJINCPPSDK_ABSTRACTGRAPHQLRESPONSE_HPP
#define ENJINCPPSDK_ABSTRACTGRAPHQLRESPONSE_HPP

#include "enjinsdk/GraphqlError.hpp"
#include "enjinsdk/models/PaginationCursor.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <optional>
#include <vector>

namespace enjin::sdk::graphql {

/// \brief Base class which models common functionality for GraphQL responses.
class AbstractGraphqlResponse {
public:
    /// \brief Default destructor.
    virtual ~AbstractGraphqlResponse() = default;

    /// \brief Returns the GraphQL errors.
    /// \return Optional for the errors.
    std::optional<std::vector<GraphqlError>> get_errors() {
        return errors;
    }

    /// \brief Returns the pagination cursor.
    /// \return Optional for the cursor.
    std::optional<enjin::sdk::models::PaginationCursor> get_cursor() {
        return cursor;
    }

    /// \brief Determines if the response has errors or not.
    /// \return Whether this response has errors.
    bool has_errors() noexcept {
        return errors.has_value() && !errors.value().empty();
    }

    /// \brief Determines if the response is empty or not.
    /// \return Whether this response does not have a result.
    virtual bool is_empty() noexcept = 0;

    /// \brief Determines if the response is successful or not.
    /// \return Whether this response is successful.
    /// \remark A response is considered successful if it has no errors and is not empty.
    bool is_successful() noexcept {
        return !(is_empty() || has_errors());
    }

    /// \brief Determines if the response is paginated or not.
    /// \return Whether this response is paginated.
    bool is_paginated() noexcept {
        return cursor.has_value();
    }

protected:
    std::optional<std::vector<GraphqlError>> errors;
    std::optional<enjin::sdk::models::PaginationCursor> cursor;

    static constexpr char DATA_KEY[] = "data";
    static constexpr char RESULT_KEY[] = "result";
    static constexpr char ITEMS_KEY[] = "items";
    static constexpr char CURSOR_KEY[] = "cursor";
    static constexpr char ERROR_KEY[] = "error";
    static constexpr char ERRORS_KEY[] = "errors";

    void process(const char* json) {
        rapidjson::Document document;
        document.Parse(json);
        if (document.IsObject()) {
            if (document.HasMember(DATA_KEY) && document[DATA_KEY].IsObject()) {
                process_data(document);
            } else if (document.HasMember(ERROR_KEY) && document[ERROR_KEY].IsObject()) {
                process_errors(document);
            }
        }
    }

    virtual void process_data(const rapidjson::Document& document) = 0;

    void process_errors(const rapidjson::Document& document) {
        auto error_obj = document[ERROR_KEY].GetObject();
        if (!error_obj.HasMember(ERRORS_KEY) && error_obj[ERRORS_KEY].IsArray()) {
            return;
        }

        std::vector<GraphqlError> list;
        for (auto& v : error_obj[ERRORS_KEY].GetArray()) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            v.Accept(writer);
            const char* error_json = buffer.GetString();

            GraphqlError error;
            error.deserialize(error_json);
            list.push_back(error);
        }
        errors.emplace(list);
    }
};

}

#endif //ENJINCPPSDK_ABSTRACTGRAPHQLRESPONSE_HPP
