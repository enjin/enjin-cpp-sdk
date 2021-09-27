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

#ifndef ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
#define ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/GraphqlQueryRegistry.hpp"
#include "enjinsdk/IHttpClient.hpp"
#include "enjinsdk/TrustedPlatformHandler.hpp"
#include <memory>
#include <string>

namespace enjin::sdk {

/// \brief The middleware used by clients to communicate with the platform.
class ENJINSDK_EXPORT TrustedPlatformMiddleware {
public:
    TrustedPlatformMiddleware() = delete;

    /// \brief Constructs the middleware with the underlying HTTP client and debug option.
    /// \param client The HTTP client.
    explicit TrustedPlatformMiddleware(std::unique_ptr<http::IHttpClient> client);

    /// \brief Default move constructor.
    /// \param middleware The middleware to move.
    TrustedPlatformMiddleware(TrustedPlatformMiddleware&& middleware) = default;

    /// \brief Default destructor.
    ~TrustedPlatformMiddleware() = default;

    /// \brief Returns the query registry used by the middleware.
    /// \return The query registry.
    [[nodiscard]] const graphql::GraphqlQueryRegistry& get_query_registry() const;

    /// \brief Returns the HTTP client used by the middleware.
    /// \return The HTTP client.
    [[nodiscard]] const std::unique_ptr<http::IHttpClient>& get_client() const;

    /// \brief Returns the Trusted Platform handler used by the middleware.
    /// \return The Trusted Platform handler.
    [[nodiscard]] const std::shared_ptr<http::TrustedPlatformHandler>& get_handler() const;

private:
    graphql::GraphqlQueryRegistry query_registry;
    std::unique_ptr<http::IHttpClient> client;
    std::shared_ptr<http::TrustedPlatformHandler> handler = std::make_shared<http::TrustedPlatformHandler>();
};

}

#endif //ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
