#ifndef ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
#define ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL

#ifndef ENJINCPPSDK_HTTPCLIENTIMPL_HPP
#define ENJINCPPSDK_HTTPCLIENTIMPL_HPP

#include "enjinsdk_export.h"
#include "cpprest/http_client.h"
#include "enjinsdk/IHttpClient.hpp"
#include "enjinsdk/Logger.hpp"
#include <future>
#include <memory>
#include <string>

namespace enjin::sdk::http {

/// \brief Implementation class for an HTTP client base on Microsoft's C++ Rest SDK.
class ENJINSDK_EXPORT HttpClientImpl : public IHttpClient {
public:
    HttpClientImpl() = delete;

    /// \brief Creates the HTTP client with the base URI.
    /// \param base_uri The base URI for the client.
    /// \param logger The logger. Null pointer by default.
    explicit HttpClientImpl(std::string base_uri, std::shared_ptr<utils::Logger> logger = nullptr);

    ~HttpClientImpl() override = default;

    std::future<HttpResponse> send_request(const HttpRequest& request) override;

    void set_trusted_platform_handler(std::shared_ptr<http::TrustedPlatformHandler> handler) override;

private:
    std::string base_uri;
    web::http::client::http_client http_client;
    std::shared_ptr<http::TrustedPlatformHandler> tp_handler;
    std::shared_ptr<utils::Logger> logger;

    web::http::client::http_client create_http_client();
};

}

#endif //ENJINCPPSDK_HTTPCLIENTIMPL_HPP
#endif
