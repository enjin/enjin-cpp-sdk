#ifndef ENJINCPPSDK_MOCKHTTPSERVER_HPP
#define ENJINCPPSDK_MOCKHTTPSERVER_HPP

#include "cpprest/http_listener.h"
#include "cpprest/http_msg.h"
#include <vector>

namespace enjin::test::utils {

class MockHttpServer {
    // TODO: Add method to map a stub-response for a given request.
public:
    MockHttpServer();

    ~MockHttpServer() = default;

    void start();

    void shutdown();

    void enqueue(const web::http::http_response& response);

    web::http::uri uri(const std::string& path);

private:
    web::http::experimental::listener::http_listener listener;
    std::vector<web::http::http_response> response_queue;
};

}

#endif //ENJINCPPSDK_MOCKHTTPSERVER_HPP
