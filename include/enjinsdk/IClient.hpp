#ifndef ENJINCPPSDK_ICLIENT_HPP
#define ENJINCPPSDK_ICLIENT_HPP

#include "enjinsdk_export.h"
#include <string>

namespace enjin::sdk {

/// \brief Interface for client implementation.
class ENJINSDK_EXPORT IClient {
public:
    /// \brief Default destructor.
    virtual ~IClient() = default;

    /// \brief Authenticates this client with the given token.
    /// \param token The auth token.
    virtual void auth(const std::string& token) = 0;

    /// \brief Determines if this client is authenticated.
    /// \return Whether this client is authenticated.
    virtual bool is_authenticated() = 0;
};

}

#endif //ENJINCPPSDK_ICLIENT_HPP
