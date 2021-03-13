#ifndef ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
#define ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL

#ifndef ENJINCPPSDK_HTTPCLIENTIMPL_HPP
#define ENJINCPPSDK_HTTPCLIENTIMPL_HPP

#include "enjinsdk_export.h"
#include "cpprest/http_client.h"
#include "enjinsdk/IHttpClient.hpp"
#include <future>
#include <string>

namespace enjin::sdk::http {

/// \brief Implementation class for an HTTP client base on Microsoft's C++ Rest SDK.
class ENJINSDK_EXPORT HttpClientImpl : public IHttpClient {
public:
    HttpClientImpl() = delete;

    /// \brief Creates the HTTP client and assigns a base URI.
    /// \param base_uri The base URI for the client.
    explicit HttpClientImpl(const std::string& base_uri);

    ~HttpClientImpl() override = default;

    void close() override;

    std::future<HttpResponse> send_request(const HttpRequest& request) override;

    void set_trusted_platform_handler(std::shared_ptr<http::TrustedPlatformHandler> handler) override;

private:
    web::http::client::http_client http_client;
    std::shared_ptr<http::TrustedPlatformHandler> tp_handler;
};

}

#endif //ENJINCPPSDK_HTTPCLIENTIMPL_HPP
#endif
