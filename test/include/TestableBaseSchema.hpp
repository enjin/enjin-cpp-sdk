#ifndef ENJINSDK_TESTABLEBASESCHEMA_HPP
#define ENJINSDK_TESTABLEBASESCHEMA_HPP

#include "enjinsdk/BaseSchema.hpp"
#include <string>

namespace enjin::test::utils {

class TestableBaseSchema : public sdk::BaseSchema {
public:
    TestableBaseSchema();

    explicit TestableBaseSchema(sdk::TrustedPlatformMiddleware middleware);

    ~TestableBaseSchema() = default;

    const sdk::TrustedPlatformMiddleware& get_middleware();

    std::string create_request_body(sdk::graphql::AbstractGraphqlRequest& request);

    sdk::http::HttpRequest create_request(sdk::graphql::AbstractGraphqlRequest& request);

    template<class T>
    std::future<sdk::graphql::GraphqlResponse<T>> send_request_for_one(sdk::graphql::AbstractGraphqlRequest& request) {
        return BaseSchema::send_request_for_one<T>(request);
    }

    template<class T>
    std::future<sdk::graphql::GraphqlResponse<std::vector<T>>>
    send_request_for_many(sdk::graphql::AbstractGraphqlRequest& request) {
        return BaseSchema::send_request_for_many<T>(request);
    }
};

}

#endif //ENJINSDK_TESTABLEBASESCHEMA_HPP
