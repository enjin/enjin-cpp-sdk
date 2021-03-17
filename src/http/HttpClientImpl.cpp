#include "HttpClientImpl.hpp"

#include <sstream>
#include <utility>

namespace enjin::sdk::http {

HttpClientImpl::HttpClientImpl(std::string base_uri, std::shared_ptr<utils::Logger> logger)
        : base_uri(std::move(base_uri)),
          http_client(create_http_client()),
          logger(std::move(logger)) {
}

std::future<HttpResponse> HttpClientImpl::send_request(const HttpRequest& request) {
    return std::async([this, request] {
        try {
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
        } catch (const std::exception& e) {
            std::stringstream ss;
            ss << "HTTP request failed: " << e.what();
            logger->log(utils::LogLevel::SEVERE, ss.str());
            throw e;
        }
    });
}

void HttpClientImpl::set_trusted_platform_handler(std::shared_ptr<http::TrustedPlatformHandler> handler) {
    tp_handler = handler;
}

web::http::client::http_client HttpClientImpl::create_http_client() {
    web::http::client::http_client client(utility::conversions::to_string_t(base_uri));

    client.add_handler([this](web::http::http_request request,
                              const std::shared_ptr<web::http::http_pipeline_stage>& pipeline_stage) {
        // Adds the default SDK user agent header using the defined SDK version if the definitions were set
        std::stringstream user_agent_ss;
        user_agent_ss << TrustedPlatformHandler::USER_AGENT_PREFIX;

#ifdef ENJINSDK_VERSION
        user_agent_ss << ENJINSDK_VERSION;
#else
        user_agent_ss << "?";
#endif

        auto user_agent_value = utility::conversions::to_string_t(user_agent_ss.str());

        if (request.headers().has(web::http::header_names::user_agent)) {
            request.headers().remove(web::http::header_names::user_agent);
        }
        request.headers().add(web::http::header_names::user_agent, user_agent_value);

        if (tp_handler != nullptr && tp_handler->is_authenticated()) {
            std::stringstream header_value_ss;
            header_value_ss << TrustedPlatformHandler::AUTHORIZATION_SCHEMA
                            << " "
                            << tp_handler->get_auth_token().value();

            auto header_name = utility::conversions::to_string_t(TrustedPlatformHandler::AUTHORIZATION);
            auto header_value = utility::conversions::to_string_t(header_value_ss.str());

            request.headers().add(header_name, header_value); // Results in "Authorization: Bearer <auth_token>"
        }

        return pipeline_stage->propagate(request);
    });

    return client;
}

}
