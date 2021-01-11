#ifndef ENJINCPPSDK_ABSTRACTHTTPCLIENT_HPP
#define ENJINCPPSDK_ABSTRACTHTTPCLIENT_HPP

#include "enjinsdk/HttpRequest.hpp"
#include "enjinsdk/HttpResponse.hpp"
#include <future>
#include <string>

namespace enjin::sdk::http {

// TODO: Add constructor argument to add a HTTP interceptor/handler.

/// \brief Abstract HTTP client class to be used for interfacing with the SDK.
class AbstractHttpClient {
public:
    constexpr static char CONTENT_TYPE[] = "application/json; charset=utf-8"; // TODO: Move to a class for defined consts.

    AbstractHttpClient() = delete;

    /// \brief Creates the HTTP client and assigns a base URI.
    /// \param base_uri The base URI for the client.
    explicit AbstractHttpClient(std::string base_uri);

    /// \brief Default destructor.
    /// \remarks The destructor does not necessarily close the client.
    virtual ~AbstractHttpClient() = default;

    /// \brief Closes the connection and releases resources.
    virtual void close() = 0;

    /// \brief Sends an HTTP request asynchronously.
    /// \param request The HTTP request.
    /// \return The future for accessing the response.
    virtual std::future<HttpResponse> send_request(const HttpRequest& request) = 0;

    /// \brief Returns the base URI string of this client.
    /// \return The base URI.
    std::string get_base_uri();

private:
    std::string base_uri;
};

}

#endif //ENJINCPPSDK_ABSTRACTHTTPCLIENT_HPP
