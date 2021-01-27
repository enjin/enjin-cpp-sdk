#ifndef ENJINCPPSDK_ABSTRACTGRAPHQLRESPONSE_HPP
#define ENJINCPPSDK_ABSTRACTGRAPHQLRESPONSE_HPP

#include "enjinsdk/GraphqlError.hpp"
#include "enjinsdk/models/PaginationCursor.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::graphql {

/// \brief Base class which models common functionality for GraphQL responses.
class AbstractGraphqlResponse {
public:
    /// \brief Default destructor.
    virtual ~AbstractGraphqlResponse() = default;

    /// \brief Returns the GraphQL errors.
    /// \return Optional for the errors.
    std::optional<std::vector<GraphqlError>> get_errors();

    /// \brief Returns the pagination cursor.
    /// \return Optional for the cursor.
    std::optional<enjin::sdk::models::PaginationCursor> get_cursor();

    /// \brief Determines if the response has errors or not.
    /// \return Whether this response has errors.
    bool has_errors() noexcept;

    /// \brief Determines if the response is empty or not.
    /// \return Whether this response does not have a result.
    virtual bool is_empty() noexcept = 0;

    /// \brief Determines if the response is successful or not.
    /// \return Whether this response is successful.
    /// \remark A response is considered successful if it has no errors and is not empty.
    bool is_successful() noexcept;

    /// \brief Determines if the response is paginated or not.
    /// \return Whether this response is paginated.
    bool is_paginated() noexcept;

protected:
    std::optional<std::vector<GraphqlError>> errors;
    std::optional<enjin::sdk::models::PaginationCursor> cursor;

    /// \brief Processes the serialized GraphQL response.
    /// \param json The JSON.
    void process(const std::string& json);

    /// \brief Processes the data member of a serialized GraphQL response.
    /// \param data_json The JSON string of the member.
    virtual void process_data(const std::string& data_json) = 0;

    /// \brief Processes the error member of a serialized GraphQL response.
    /// \param error_json The JSON string of the member.
    void process_errors(const std::string& error_json);
};

}

#endif //ENJINCPPSDK_ABSTRACTGRAPHQLRESPONSE_HPP
