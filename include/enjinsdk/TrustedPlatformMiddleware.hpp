#ifndef ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
#define ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP

#include "enjinsdk/GraphqlQueryRegistry.hpp"
#include "enjinsdk/AbstractHttpClient.hpp"
#include <string>

namespace enjin::sdk {

// TODO: Documentation
class TrustedPlatformMiddleware {
public:
    TrustedPlatformMiddleware() = delete;

    explicit TrustedPlatformMiddleware(enjin::sdk::http::AbstractHttpClient& client, bool debug = false);

    /// \brief Copy constructor.
    /// \param middleware
    TrustedPlatformMiddleware(const TrustedPlatformMiddleware& middleware) = default;

    ~TrustedPlatformMiddleware() = default;

    [[nodiscard]] const graphql::GraphqlQueryRegistry& get_query_registry() const;

    [[nodiscard]] http::AbstractHttpClient* get_client() const;

private:
    enjin::sdk::graphql::GraphqlQueryRegistry query_registry;
    enjin::sdk::http::AbstractHttpClient* client = nullptr; // TODO: Consider using a smart pointer instead for client.
};

}

#endif //ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
