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

#ifndef ENJINSDK_CLIENTMIDDLEWARE_HPP
#define ENJINSDK_CLIENTMIDDLEWARE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/GraphqlQueryRegistry.hpp"
#include "enjinsdk/HttpRequest.hpp"
#include "enjinsdk/IHttpClient.hpp"
#include <memory>
#include <mutex>

namespace enjin::sdk {

/// \brief Middleware class used by clients to communicate with the platform.
class ENJINSDK_EXPORT ClientMiddleware {
public:
    ClientMiddleware() = delete;

    /// \brief Constructs the middleware with the underlying HTTP client and debug option.
    /// \param client The HTTP client.
    explicit ClientMiddleware(std::unique_ptr<http::IHttpClient> client);

    ClientMiddleware(const ClientMiddleware&) = delete;

    ClientMiddleware(ClientMiddleware&&) = delete;

    /// \brief Default destructor.
    ~ClientMiddleware() = default;

    /// \brief Closes the connection with the platform.
    void close();

    /// \brief Creates a new HTTP request and sets any necessary data needed for communicating with the platform.
    /// \return The request.
    http::HttpRequest create_request() const;

    /// \brief Returns the query registry used by the middleware.
    /// \return The query registry.
    [[nodiscard]] const graphql::GraphqlQueryRegistry& get_query_registry() const;

    /// \brief Returns the HTTP client used by the middleware.
    /// \return The HTTP client.
    [[nodiscard]] const std::unique_ptr<http::IHttpClient>& get_client() const;

    /// \brief Determines whether this middleware is authenticated.
    /// \return Whether this middleware is authenticated.
    bool is_authenticated() const;

    /// \brief Determines if the connection this middleware has with the platform is closed.
    /// \return Whether the connection is closed.
    [[nodiscard]] bool is_closed() const;

    /// \brief Sets the authentication token for this middleware.
    /// \param auth_token The auth token.
    void set_auth_token(std::string token);

private:
    std::string auth_token;
    graphql::GraphqlQueryRegistry query_registry;
    std::unique_ptr<http::IHttpClient> client;

    // Mutexes
    mutable std::mutex auth_token_mutex;

    /// \brief The schema of the Authorization request header.
    static constexpr char AUTHORIZATION_SCHEMA[] = "Bearer";

    /// \brief The prefix for the default user agent value of this SDK in "<product>/<version>" format.
    static constexpr char USER_AGENT_PREFIX[] = "Enjin-CPP-SDK/v";
};

}

#endif //ENJINSDK_CLIENTMIDDLEWARE_HPP
