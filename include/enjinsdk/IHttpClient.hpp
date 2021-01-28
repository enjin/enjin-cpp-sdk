#ifndef ENJINCPPSDK_IHTTPCLIENT_HPP
#define ENJINCPPSDK_IHTTPCLIENT_HPP

#include "enjinsdk/HttpRequest.hpp"
#include "enjinsdk/HttpResponse.hpp"
#include <future>
#include <string>

namespace enjin::sdk::http {

// TODO: Add constructor argument to add a HTTP interceptor/handler.

/// \brief Abstract HTTP client class to be used for interfacing with the SDK.
class IHttpClient {
public:
    constexpr static char CONTENT_TYPE[] = "application/json; charset=utf-8"; // TODO: Move to a class for defined consts.

    /// \brief Default destructor.
    /// \remarks The destructor does not necessarily close the client.
    virtual ~IHttpClient() = default;

    /// \brief Closes the connection and releases resources.
    virtual void close() = 0;

    /// \brief Sends an HTTP request asynchronously.
    /// \param request The HTTP request.
    /// \return The future for accessing the response.
    virtual std::future<HttpResponse> send_request(const HttpRequest& request) = 0; // TODO: Consider if this should return just the response body instead.
};

}

#endif //ENJINCPPSDK_IHTTPCLIENT_HPP
