#ifndef ENJINCPPSDK_HTTPCLIENTIMPL_HPP
#define ENJINCPPSDK_HTTPCLIENTIMPL_HPP

#include "cpprest/http_client.h"
#include "enjinsdk/AbstractHttpClient.hpp"

namespace enjin::sdk::http {

class HttpClientImpl : public AbstractHttpClient {
public:
    HttpClientImpl() = delete;

    explicit HttpClientImpl(const std::string& base_uri);

    std::future<HttpResponse> send_request() override;

private:
    web::http::client::http_client http_client;
};

}

#endif //ENJINCPPSDK_HTTPCLIENTIMPL_HPP
