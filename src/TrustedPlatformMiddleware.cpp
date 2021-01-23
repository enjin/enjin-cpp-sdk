#include "enjinsdk/TrustedPlatformMiddleware.hpp"

namespace enjin::sdk {

TrustedPlatformMiddleware::TrustedPlatformMiddleware(http::AbstractHttpClient& client, bool debug) : client(&client) {
}

const graphql::GraphqlQueryRegistry& TrustedPlatformMiddleware::get_query_registry() const {
    return query_registry;
}

http::AbstractHttpClient* TrustedPlatformMiddleware::get_client() const {
    return client;
}

}
