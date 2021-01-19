#ifndef ENJINCPPSDK_BASESCHEMA_HPP
#define ENJINCPPSDK_BASESCHEMA_HPP

#include "enjinsdk/GraphqlRequest.hpp"
#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include <future>

namespace enjin::sdk {

class BaseSchema {
public:
    BaseSchema() = delete;

protected:
    TrustedPlatformMiddleware middleware;
    std::string schema;

    BaseSchema(const TrustedPlatformMiddleware& middleware, std::string schema);

    ~BaseSchema() = default;

    void create_request_body(const enjin::sdk::graphql::IGraphqlRequest& request);
};

}

#endif //ENJINCPPSDK_BASESCHEMA_HPP
