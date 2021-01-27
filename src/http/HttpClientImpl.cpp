#include "HttpClientImpl.hpp"

namespace enjin::sdk::http {

HttpClientImpl::HttpClientImpl(const std::string& base_uri) : AbstractHttpClient(base_uri),
                                                              http_client(utility::conversions::to_string_t(base_uri)) {
}

void HttpClientImpl::close() {
    // TODO: Implement close method.
}

std::future<HttpResponse> HttpClientImpl::send_request(const HttpRequest& request) {
    // TODO: Determine if 'this->http_client' introduces unsafe thread behavior.
    return std::async([this, request] {
        auto method = utility::conversions::to_string_t(request.get_method());
        auto task = http_client.request(method,
                                        request.get_path_query_fragment(),
                                        request.get_body(),
                                        request.get_content_type());

        web::http::http_response response = task.get();

        return HttpResponseBuilder()
                .code(response.status_code())
                .body(response.extract_utf8string().get())
                .content_type(utility::conversions::to_utf8string(response.headers().content_type()))
                .build();
    });
}

}
