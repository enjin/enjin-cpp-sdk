#ifndef ENJINCPPSDK_IHTTPCLIENT_HPP
#define ENJINCPPSDK_IHTTPCLIENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/HttpRequest.hpp"
#include "enjinsdk/HttpResponse.hpp"
#include <future>

namespace enjin::sdk::http {

/// \brief HTTP client interface to be used for interfacing with the Enjin SDK platform clients.
class ENJINSDK_EXPORT IHttpClient {
public:
    /// \brief Default destructor.
    virtual ~IHttpClient() = default;

    /// \brief Starts the client.
    virtual void start() = 0;

    /// \brief Stops the client.
    virtual void stop() = 0;

    /// \brief Sends an HTTP request asynchronously.
    /// \param request The HTTP request.
    /// \return The future for accessing the response.
    virtual std::future<HttpResponse> send_request(const HttpRequest& request) = 0;
};

}

#endif //ENJINCPPSDK_IHTTPCLIENT_HPP
