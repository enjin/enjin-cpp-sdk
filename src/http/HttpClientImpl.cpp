#include "HttpClientImpl.hpp"

#include <sstream>

namespace enjin::sdk::http {

HttpClientImpl::HttpClientImpl(const std::string& base_uri) : http_client(utility::conversions::to_string_t(base_uri)) {
    http_client.add_handler([this](web::http::http_request request,
                                   const std::shared_ptr<web::http::http_pipeline_stage>& pipeline_stage) {
        // Adds the default SDK user agent header using the defined SDK version if the definitions were set
        auto user_agent_value = utility::conversions::to_string_t((std::stringstream()
                << TrustedPlatformHandler::USER_AGENT_PREFIX
#ifdef ENJINSDK_VERSION_MAJOR
                << ENJINSDK_VERSION_MAJOR
#ifdef ENJINSDK_VERSION_MINOR
                << "."
                << ENJINSDK_VERSION_MINOR
#ifdef ENJINSDK_VERSION_PATCH
                << "."
                << ENJINSDK_VERSION_PATCH
#endif // ENJINSDK_VERSION_PATCH
#endif // ENJINSDK_VERSION_MINOR
#else
                << "?"
#endif // ENJINSDK_VERSION_MAJOR
                                                                  ).str());

        if (request.headers().has(web::http::header_names::user_agent)) {
            request.headers().remove(web::http::header_names::user_agent);
        }
        request.headers().add(web::http::header_names::user_agent, user_agent_value);

        if (tp_handler != nullptr && tp_handler->is_authenticated()) {
            auto header_name = utility::conversions::to_string_t(TrustedPlatformHandler::AUTHORIZATION);
            auto header_value = utility::conversions::to_string_t((std::stringstream()
                    << TrustedPlatformHandler::AUTHORIZATION_SCHEMA
                    << " "
                    << tp_handler->get_auth_token().value()
                                                                  ).str());

            request.headers().add(header_name, header_value); // Results in "Authorization: Bearer <auth_token>"
        }

        return pipeline_stage->propagate(request);
    });
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

void HttpClientImpl::set_trusted_platform_handler(std::shared_ptr<http::TrustedPlatformHandler> handler) {
    tp_handler = handler;
}

}
