#include "enjinsdk/TrustedPlatformMiddleware.hpp"

#include <utility>

namespace enjin::sdk {

TrustedPlatformMiddleware::TrustedPlatformMiddleware(std::unique_ptr<http::IHttpClient> client, bool)
        : client(std::move(client)) {
}

const graphql::GraphqlQueryRegistry& TrustedPlatformMiddleware::get_query_registry() const {
    return query_registry;
}

const std::unique_ptr<http::IHttpClient>& TrustedPlatformMiddleware::get_client() const {
    return client;
}

const std::shared_ptr<http::TrustedPlatformHandler>& TrustedPlatformMiddleware::get_handler() const {
    return handler;
}

}
