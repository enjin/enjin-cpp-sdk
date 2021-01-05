#include "HttpClientImpl.hpp"

namespace enjin::sdk::http {

HttpClientImpl::HttpClientImpl(const std::string& base_uri) : AbstractHttpClient(base_uri),
                                                              http_client(utility::conversions::to_string_t(base_uri)) {
}

std::future<HttpResponse> HttpClientImpl::send_request() {
    // TODO: Determine if 'this->http_client' introduces unsafe thread behavior.
    // TODO: Add argument(s) to lambda to pass in request information.
    return std::async([this]() {
        web::uri_builder uri_builder(utility::conversions::to_string_t("/schema"));
        web::json::value request_body;

        auto task = http_client.request(web::http::methods::POST, uri_builder.to_string(), request_body);
        task.wait();
        web::http::http_response response = task.get();

        // Status code
        uint16_t code = response.status_code();

        // Response body
        auto response_body = response.extract_string().get();
        std::string body = utility::conversions::to_utf8string(response_body);

        return HttpResponse(code, body);
    });
}

}
