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

#ifndef ENJINCPPSDK_ABSTRACTGRAPHQLRESPONSE_HPP
#define ENJINCPPSDK_ABSTRACTGRAPHQLRESPONSE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/GraphqlError.hpp"
#include "enjinsdk/models/PaginationCursor.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::graphql {

/// \brief Base class which models common functionality for GraphQL responses.
class ENJINSDK_EXPORT AbstractGraphqlResponse {
public:
    /// \brief Default destructor.
    virtual ~AbstractGraphqlResponse() = default;

    /// \brief Returns the GraphQL errors.
    /// \return Optional for the errors.
    [[nodiscard]] const std::optional<std::vector<GraphqlError>>& get_errors() const;

    /// \brief Returns the pagination cursor.
    /// \return Optional for the cursor.
    [[nodiscard]] const std::optional<enjin::sdk::models::PaginationCursor>& get_cursor() const;

    /// \brief Determines if the response has errors or not.
    /// \return Whether this response has errors.
    [[nodiscard]] bool has_errors() const noexcept;

    /// \brief Determines if the response is empty or not.
    /// \return Whether this response does not have a result.
    [[nodiscard]] virtual bool is_empty() const noexcept = 0;

    /// \brief Determines if the response is successful or not.
    /// \return Whether this response is successful.
    /// \remark A response is considered successful if it has no errors and is not empty.
    [[nodiscard]] bool is_successful() const noexcept;

    /// \brief Determines if the response is paginated or not.
    /// \return Whether this response is paginated.
    [[nodiscard]] bool is_paginated() const noexcept;

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
