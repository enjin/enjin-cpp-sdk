#include "HttpClientImpl.hpp"

#include <stdexcept>
#include <utility>

namespace enjin::sdk::http {

HttpClientImpl::HttpClientImpl(std::string base_uri, std::shared_ptr<utils::Logger> logger)
        : base_uri(std::move(base_uri)),
          logger(std::move(logger)) {
}

HttpClientImpl::~HttpClientImpl() {
    stop();
}

void HttpClientImpl::start() {
    http_client = std::make_unique<httplib::Client>(base_uri.c_str());
    http_client->set_keep_alive(true);
    // TODO: Setup logger in http_client.
}

void HttpClientImpl::stop() {
    http_client->stop(); // TODO: Check if client is running.
}

std::future<HttpResponse> HttpClientImpl::send_request(const HttpRequest& request) {
    return std::async([this, request] {
        if (request.get_method() != HttpMethod::Post) {
            throw std::runtime_error("HTTP method for request is not 'POST'");
        }

        auto res = http_client->Post(request.get_path_query_fragment().c_str(),
                                     create_headers(request),
                                     request.get_body(),
                                     request.get_content_type().c_str());
        if (res) {
            return HttpResponseBuilder()
                    .code(res->status)
                    .body(res->body)
                    .content_type(res->get_header_value("Content-Type"))
                    .build();
        } else {
            /* TODO: Handle errors/exceptions on response.
             * TODO: Log message* and throw exception.
             *       * Logging may also be done by setting a logger for http_client.
             */
            if (logger != nullptr) {
                logger->log(utils::LogLevel::SEVERE, "");
            }

            throw std::runtime_error("");
        }
    });
}

httplib::Headers HttpClientImpl::create_headers(const HttpRequest& request) {
    httplib::Headers headers;

    for (const auto& entry : request.get_headers()) {
        headers.emplace(entry.first, entry.second);
    }

    return headers;
}

}
