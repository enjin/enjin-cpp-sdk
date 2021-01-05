#include "enjinsdk/BaseSchema.hpp"

namespace enjin::sdk {

BaseSchema::BaseSchema(TrustedPlatformMiddleware middleware, const char* schema) : middleware(middleware),
                                                                                   schema(schema) {
}

void BaseSchema::create_request_body(const enjin::sdk::graphql::IGraphqlRequest& request) {

}

}
