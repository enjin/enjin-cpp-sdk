#ifndef ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
#define ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP

#include "enjinsdk/GraphqlQueryRegistry.hpp"
#include "enjinsdk/IHttpClient.hpp"
#include <memory>
#include <string>

namespace enjin::sdk {

/// \brief The middleware used by clients to communicate with the platform.
class TrustedPlatformMiddleware {
public:
    TrustedPlatformMiddleware() = delete;

    /// \brief Constructs the middleware with the underlying HTTP client and debug option.
    /// \param client The HTTP client.
    /// \param debug Whether debugging is enabled.
    explicit TrustedPlatformMiddleware(std::unique_ptr<http::IHttpClient> client, bool debug = false);

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

private:
    graphql::GraphqlQueryRegistry query_registry;
    std::unique_ptr<http::IHttpClient> client;
};

}

#endif //ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
