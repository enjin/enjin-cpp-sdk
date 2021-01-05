#include "enjinsdk/TrustedPlatformMiddleware.hpp"

namespace enjin::sdk {

enjin::sdk::graphql::GraphqlQueryRegistry& TrustedPlatformMiddleware::get_query_registry() {
    return query_registry;
}

}
