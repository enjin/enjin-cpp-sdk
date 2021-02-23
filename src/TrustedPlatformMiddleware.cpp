#include "enjinsdk/TrustedPlatformMiddleware.hpp"

#include <utility>

namespace enjin::sdk {

TrustedPlatformMiddleware::TrustedPlatformMiddleware(std::unique_ptr<http::IHttpClient> client, bool debug)
        : client(std::move(client)) {
}

const graphql::GraphqlQueryRegistry& TrustedPlatformMiddleware::get_query_registry() const {
    return query_registry;
}

const std::unique_ptr<http::IHttpClient>& TrustedPlatformMiddleware::get_client() const {
    return client;
}

}
