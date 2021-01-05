#ifndef ENJINCPPSDK_BASESCHEMA_HPP
#define ENJINCPPSDK_BASESCHEMA_HPP

#include "enjinsdk/GraphqlRequest.hpp"
#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include <future>

namespace enjin::sdk {

/// \brief
class BaseSchema {
public:
    /// \brief
    BaseSchema() = delete;

protected:
    TrustedPlatformMiddleware middleware;
    std::string schema;

    /// \brief
    /// \param middleware
    /// \param schema
    BaseSchema(TrustedPlatformMiddleware middleware, const char* schema);

    /// \brief
    ~BaseSchema() = default;

    void create_request_body(const enjin::sdk::graphql::IGraphqlRequest& request);
};

}

#endif //ENJINCPPSDK_BASESCHEMA_HPP
