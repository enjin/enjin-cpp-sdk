#ifndef ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
#define ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP

#include "enjinsdk/GraphqlQueryRegistry.hpp"
#include "enjinsdk/IHttpClient.hpp"
#include <string>

namespace enjin::sdk {

/// \brief The middleware used by clients to communicate with the platform.
class TrustedPlatformMiddleware {
public:
    TrustedPlatformMiddleware() = delete;

    /// \brief Constructs the middleware with the underlying HTTP client and debug option.
    /// \param client The HTTP client.
    /// \param debug Whether debugging is enabled.
    explicit TrustedPlatformMiddleware(http::IHttpClient& client, bool debug = false);

    /// \brief Copy constructor.
    /// \param middleware The middleware.
    TrustedPlatformMiddleware(const TrustedPlatformMiddleware& middleware) = default;

    /// \brief Default destructor.
    ~TrustedPlatformMiddleware() = default;

    /// \brief Returns the query registry used by the middleware.
    /// \return The query registry.
    [[nodiscard]] const graphql::GraphqlQueryRegistry& get_query_registry() const;

    /// \brief Returns the HTTP client used by the middleware.
    /// \return The HTTP client.
    [[nodiscard]] http::IHttpClient* get_client() const;

private:
    graphql::GraphqlQueryRegistry query_registry;
    http::IHttpClient* client = nullptr; // TODO: Consider using a smart pointer instead for client.
};

}

#endif //ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
