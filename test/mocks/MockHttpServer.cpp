#include "MockHttpServer.hpp"

namespace enjin::test::utils {

enjin::sdk::http::HttpRequest casablanca_to_enjin_request(web::http::http_request casablanca_req) {
    return enjin::sdk::http::HttpRequestBuilder()
            .method(utility::conversions::to_utf8string(casablanca_req.method()))
            .path_query_fragment(utility::conversions::to_utf8string(casablanca_req.request_uri().to_string()))
            .body(casablanca_req.extract_utf8string().get())
            .content_type(utility::conversions::to_utf8string(casablanca_req.headers().content_type()))
            .build();
}

web::http::http_response enjin_to_casablanca_response(enjin::sdk::http::HttpResponse enjin_res) {
    web::http::http_response casablanca_res;

    if (enjin_res.get_code().has_value()) {
        casablanca_res.set_status_code(enjin_res.get_code().value());
    }
    if (enjin_res.get_body().has_value()) {
        if (enjin_res.get_content_type().has_value() && !enjin_res.get_content_type().value().empty()) {
            casablanca_res.set_body(enjin_res.get_body().value(),
                                    enjin_res.get_content_type().value());
        } else {
            casablanca_res.set_body(enjin_res.get_body().value());
        }
    }

    return casablanca_res;
}

MockHttpServer::MockHttpServer() {
    // TODO: Make the port # dynamic if necessary.
    listener = web::http::experimental::listener::http_listener(U("http://localhost:8080/"));

    // Sets the listener to support any request by replying with the response in the front of the queue
    listener.support([this](const web::http::http_request& request) {
        auto mapped_response_loc = request_response_map.find(casablanca_to_enjin_request(request));

        if (mapped_response_loc != request_response_map.end()) {
            enjin::sdk::http::HttpResponse response = mapped_response_loc->second;
            request.reply(enjin_to_casablanca_response(response));
        } else {
            request.reply(web::http::status_codes::TooManyRequests);
        }
    });
}

void MockHttpServer::start() {
    listener.open().wait();
}

void MockHttpServer::shutdown() {
    listener.close();
}

void MockHttpServer::map_response_for_request(const enjin::sdk::http::HttpRequest& request,
                                              const enjin::sdk::http::HttpResponse& response) {
    request_response_map.try_emplace(request, response);
}

web::http::uri MockHttpServer::uri(const std::string& path) {
    return web::http::uri_builder(listener.uri())
            .append_path(utility::conversions::to_string_t(path))
            .to_uri();
}

}
