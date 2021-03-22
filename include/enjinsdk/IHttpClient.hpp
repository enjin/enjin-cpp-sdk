#ifndef ENJINCPPSDK_IHTTPCLIENT_HPP
#define ENJINCPPSDK_IHTTPCLIENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/HttpRequest.hpp"
#include "enjinsdk/HttpResponse.hpp"
#include "enjinsdk/TrustedPlatformHandler.hpp"
#include <functional>
#include <future>
#include <memory>
#include <string>

namespace enjin::sdk::http {

/// \brief HTTP client interface to be used for interfacing with the Enjin SDK platform clients.
class ENJINSDK_EXPORT IHttpClient {
public:
    /// \brief Default destructor.
    /// \remarks The destructor does not necessarily close the client.
    virtual ~IHttpClient() = default;

    /// \brief Sends an HTTP request asynchronously.
    /// \param request The HTTP request.
    /// \return The future for accessing the response.
    virtual std::future<HttpResponse> send_request(const HttpRequest& request) = 0;

    /// \brief Sets the Trusted Platform handler for the HTTP client.
    /// \param handler The handler.
    /// \remarks The handler holds data that may need to be added to outgoing requests, such as adding the authorization
    /// header with the schema and token if authenticated. The client is expected to have the logic for doing so.
    virtual void set_trusted_platform_handler(std::shared_ptr<http::TrustedPlatformHandler> handler) = 0;
};

}

#endif //ENJINCPPSDK_IHTTPCLIENT_HPP
