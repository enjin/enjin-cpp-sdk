#ifndef ENJINCPPSDK_MOCKHTTPSERVER_HPP
#define ENJINCPPSDK_MOCKHTTPSERVER_HPP

#include "enjinsdk/HttpRequest.hpp"
#include "enjinsdk/HttpResponse.hpp"
#include "cpprest/http_listener.h"
#include "cpprest/http_msg.h"
#include <map>
#include <string>

namespace enjin::test::utils {

/// \brief Mock HTTP server built on Microsoft's C++ Rest SDK for testing HTTP client implementation.
class MockHttpServer {
public:
    /// \brief Constructs a mock server instance.
    MockHttpServer();

    /// \brief Default destructor.
    /// \remarks Does not shutdown the server.
    ~MockHttpServer() = default;

    /// \brief Method to start the server.
    void start();

    /// \brief Method to shutdown the server.
    void shutdown();

    /// \brief Creating a mapping for an expected request and stubbed response.
    /// \param request The request to expect.
    /// \param response The response to reply with.
    void map_response_for_request(const enjin::sdk::http::HttpRequest& request,
                                  const enjin::sdk::http::HttpResponse& response);

    /// \brief Returns the URI for this server.
    /// \param path Optional path to extend the URI by.
    /// \return The URI.
    web::http::uri uri(const std::string& path = "/");

private:
    web::http::experimental::listener::http_listener listener;
    std::map<enjin::sdk::http::HttpRequest, enjin::sdk::http::HttpResponse> request_response_map;
};

}

#endif //ENJINCPPSDK_MOCKHTTPSERVER_HPP
