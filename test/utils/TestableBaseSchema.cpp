#include "TestableBaseSchema.hpp"

#include <utility>

namespace enjin::test::utils {

TestableBaseSchema::TestableBaseSchema()
        : TestableBaseSchema(sdk::TrustedPlatformMiddleware(nullptr, false)) {
}

TestableBaseSchema::TestableBaseSchema(sdk::TrustedPlatformMiddleware middleware)
        : BaseSchema(std::move(middleware), "test", nullptr) {

}

const sdk::TrustedPlatformMiddleware& TestableBaseSchema::get_middleware() {
    return middleware;
}

std::string TestableBaseSchema::create_request_body(sdk::graphql::AbstractGraphqlRequest& request) {
    return BaseSchema::create_request_body(request);
}

sdk::http::HttpRequest TestableBaseSchema::create_request(sdk::graphql::AbstractGraphqlRequest& request) {
    return BaseSchema::create_request(request);
}

}
