#include "enjinsdk/BaseSchema.hpp"

#include <utility>

namespace enjin::sdk {

BaseSchema::BaseSchema(const TrustedPlatformMiddleware& middleware, std::string schema)
        : middleware(middleware), schema(std::move(schema)) {
}

void BaseSchema::create_request_body(const enjin::sdk::graphql::IGraphqlRequest& request) {

}

}
