#include "enjinsdk/TrustedPlatformMiddleware.hpp"

namespace enjin::sdk {

TrustedPlatformMiddleware::TrustedPlatformMiddleware(http::IHttpClient& client, bool debug) : client(&client) {
}

const graphql::GraphqlQueryRegistry& TrustedPlatformMiddleware::get_query_registry() const {
    return query_registry;
}

http::IHttpClient* TrustedPlatformMiddleware::get_client() const {
    return client;
}

}
