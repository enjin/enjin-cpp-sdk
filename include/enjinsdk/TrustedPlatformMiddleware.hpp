#ifndef ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
#define ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP

#include "enjinsdk/GraphqlQueryRegistry.hpp"
#include "enjinsdk/AbstractHttpClient.hpp"
#include <string>

namespace enjin::sdk {

/// \brief
class TrustedPlatformMiddleware {
public:
    // TODO: Add arguments for constructing middleware.
    TrustedPlatformMiddleware() = default;

    /// \brief
    ~TrustedPlatformMiddleware() = default;

    /// \brief
    /// \return
    enjin::sdk::graphql::GraphqlQueryRegistry& get_query_registry();

private:
    std::string base_url;
    enjin::sdk::graphql::GraphqlQueryRegistry query_registry;
};

}

#endif //ENJINCPPSDK_TRUSTEDPLATFORMMIDDLEWARE_HPP
