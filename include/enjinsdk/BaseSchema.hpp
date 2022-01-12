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

#ifndef ENJINCPPSDK_BASESCHEMA_HPP
#define ENJINCPPSDK_BASESCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/LoggerProvider.hpp"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include <exception>
#include <future>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace enjin::sdk {

/// \brief Base class for schema with functionality to send GraphQL requests to the platform and process the responses.
class ENJINSDK_EXPORT BaseSchema {
public:
    BaseSchema() = delete;

    BaseSchema(const BaseSchema&) = delete;

    /// \brief Default destructor.
    ~BaseSchema() = default;

    /// \brief Returns the logger provider used by this schema.
    /// \return The logger provider.
    [[nodiscard]] const std::shared_ptr<utils::LoggerProvider>& get_logger_provider() const;

protected:
    /// \brief The middleware for communicating with the platform.
    TrustedPlatformMiddleware middleware;

    /// \brief The logger provider.
    std::shared_ptr<utils::LoggerProvider> logger_provider;

    /// \brief The name of this schema.
    std::string schema;

    /// \brief The sole constructor for a base schema.
    /// \param middleware The platform middleware.
    /// \param schema The name of the schema.
    /// \param logger_provider The logger provider. Null pointer by default.
    BaseSchema(TrustedPlatformMiddleware middleware,
               std::string schema,
               std::shared_ptr<utils::LoggerProvider> logger_provider = nullptr);

    /// \brief Move constructor.
    /// \param rhs The schema being moved.
    BaseSchema(BaseSchema&& rhs) = default;

    /// \brief Creates the serialized request body to be sent to the platform.
    /// \param request The request.
    /// \return The serialized request body.
    [[nodiscard]] std::string create_request_body(graphql::AbstractGraphqlRequest& request) const;

    /// \brief Creates an HTTP request with the passed GraphQL request as its body.
    /// \param request The GraphQL request.
    /// \return The HTTP request.
    [[nodiscard]] http::HttpRequest create_request(graphql::AbstractGraphqlRequest& request) const;

    /// \brief Sends a request for one object from the platform.
    /// \tparam T The type contained by the response.
    /// \param request The request to being sent.
    /// \return The future containing the response.
    template<class T>
    std::future<graphql::GraphqlResponse<T>> send_request_for_one(graphql::AbstractGraphqlRequest& request) {
        return std::async([this, http_request = create_request(request)] {
            try {
                auto http_response = send_request(http_request);
                return graphql::GraphqlResponse<T>(http_response.get_body().value());
            } catch (const std::exception& e) {
                log_graphql_exception(e);
                throw e;
            }
        });
    }

    /// \brief Sends a request for many objects from the platform.
    /// \tparam T The type contained the response's vector.
    /// \param request The request to being sent.
    /// \return The future containing the response.
    template<class T>
    std::future<graphql::GraphqlResponse<std::vector<T>>>
    send_request_for_many(graphql::AbstractGraphqlRequest& request) {
        return std::async([this, http_request = create_request(request)]() {
            try {
                auto http_response = send_request(std::move(http_request));
                return graphql::GraphqlResponse<std::vector<T>>(http_response.get_body().value());
            } catch (const std::exception& e) {
                log_graphql_exception(e);
                throw e;
            }
        });
    }

private:
    static constexpr char JSON[] = "application/json; charset=utf-8";

    void log_graphql_exception(const std::exception& e);

    http::HttpResponse send_request(http::HttpRequest request);
};

}

#endif //ENJINCPPSDK_BASESCHEMA_HPP
