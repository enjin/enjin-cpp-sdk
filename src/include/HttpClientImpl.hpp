#ifndef ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
#define ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0
#endif

#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL

#ifndef ENJINCPPSDK_HTTPCLIENTIMPL_HPP
#define ENJINCPPSDK_HTTPCLIENTIMPL_HPP

#include "enjinsdk_export.h"
#include "httplib.h"
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

    ~HttpClientImpl() override;

    void start() override;

    void stop() override;

    std::future<HttpResponse> send_request(const HttpRequest& request) override;

private:
    const std::string base_uri;

    std::unique_ptr<httplib::Client> http_client;
    std::shared_ptr<utils::Logger> logger;

    static httplib::Headers create_headers(const HttpRequest& request);
};

}

#endif //ENJINCPPSDK_HTTPCLIENTIMPL_HPP

#endif
