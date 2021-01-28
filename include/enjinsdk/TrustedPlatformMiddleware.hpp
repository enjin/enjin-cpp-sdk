#ifndef ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
#define ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP

#include "enjinsdk/GraphqlQueryRegistry.hpp"
#include "enjinsdk/IHttpClient.hpp"
#include <string>

namespace enjin::sdk {

// TODO: Documentation
class TrustedPlatformMiddleware {
public:
    TrustedPlatformMiddleware() = delete;

    explicit TrustedPlatformMiddleware(http::IHttpClient& client, bool debug = false);

    /// \brief Copy constructor.
    /// \param middleware
    TrustedPlatformMiddleware(const TrustedPlatformMiddleware& middleware) = default;

    ~TrustedPlatformMiddleware() = default;

    [[nodiscard]] const graphql::GraphqlQueryRegistry& get_query_registry() const;

    [[nodiscard]] http::IHttpClient* get_client() const;

private:
    graphql::GraphqlQueryRegistry query_registry;
    http::IHttpClient* client = nullptr; // TODO: Consider using a smart pointer instead for client.
};

}

#endif //ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
