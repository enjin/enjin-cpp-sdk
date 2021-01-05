#include "MockHttpServer.hpp"

namespace enjin::test::utils {

MockHttpServer::MockHttpServer() {
    // TODO: Make the port # dynamic if necessary.
    /*
    web::uri_builder builder;
    builder.set_scheme(U("http"))
           .set_host(U("127.0.0.1"))
           .set_port(8080);*/

    listener = web::http::experimental::listener::http_listener(U("http://localhost:8080/"));

    // Sets the listener to support any request by replying with the response in the front of the queue
    listener.support([this](const web::http::http_request& request) {
        if (this->response_queue.empty()) {
            // TODO: Change handling of empty response queue if appropriate.
            request.reply(web::http::status_codes::TooManyRequests);
        } else {
            auto& response = this->response_queue.front();
            this->response_queue.erase(this->response_queue.begin());
            request.reply(response);
        }
    });
}

void MockHttpServer::start() {
    listener.open().wait();
}

void MockHttpServer::shutdown() {
    listener.close();
}

void MockHttpServer::enqueue(const web::http::http_response& response) {
    response_queue.push_back(response);
}

web::http::uri MockHttpServer::uri(const std::string& path) {
    return web::http::uri_builder(listener.uri())
            .append_path(utility::conversions::to_string_t(path))
            .to_uri();
}

}
