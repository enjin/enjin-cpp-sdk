#include "MockHttpServer.hpp"

#include "httplib.h"
#include <map>
#include <sstream>
#include <stdexcept>
#include <thread>

namespace enjin::test::mocks {

void ResponseProvider::respond_with(const sdk::http::HttpResponse& response) {
    if (!response.get_body().has_value()) {
        throw std::runtime_error("Stub response does not have a body");
    } else if (!response.get_content_type().has_value()) {
        throw std::runtime_error("Stub response does not have content-type");
    }

    ResponseProvider::response.emplace(response);
}

const std::optional<sdk::http::HttpResponse>& ResponseProvider::get_response() const {
    return response;
}

class MockHttpServerImpl {
public:
    MockHttpServerImpl() {
        if (!server.set_mount_point("/", "./")) {
            throw std::runtime_error("The base directory does not exist");
        } else if (!server.is_valid()) {
            throw std::runtime_error("Server is not valid");
        }
    }

    ~MockHttpServerImpl() {
        stop();
    }

    void start() {
        stop();

        std::lock_guard<std::mutex> guard(server_mutex);
        port = server.bind_to_any_port("localhost");
        server_thread = std::thread([this]() {
            server.listen_after_bind();
        });
    }

    void stop() {
        std::lock_guard<std::mutex> guard(server_mutex);

        if (server.is_running()) {
            port.reset();
            server.stop();
            server_thread.join();
        }
    }

    ResponseProvider& given(const sdk::http::HttpRequest& request) {
        std::lock_guard<std::mutex> guard(server_mutex);

        response_provider_map[request.get_path_query_fragment()] = std::make_unique<ResponseProvider>();
        auto& provider = response_provider_map[request.get_path_query_fragment()];
        auto handler = create_handler(provider);

        if (request.get_method() == "GET") {
            server.Get(request.get_path_query_fragment().c_str(), handler);
        } else if (request.get_method() == "POST") {
            server.Post(request.get_path_query_fragment().c_str(), handler);
        } else if (request.get_method() == "PUT") {
            server.Put(request.get_path_query_fragment().c_str(), handler);
        } else if (request.get_method() == "DELETE") {
            server.Delete(request.get_path_query_fragment().c_str(), handler);
        } else {
            // TODO: Handle other HTTP methods.
        }

        return *provider;
    }

    std::string uri() {
        std::lock_guard<std::mutex> guard(server_mutex);

        if (!port.has_value()) {
            throw std::runtime_error("Port number is not set");
        }

        std::stringstream ss;
        ss << "http://localhost:" << port.value();
        return ss.str();
    }

private:
    httplib::Server server;
    std::map<std::string, std::unique_ptr<ResponseProvider>> response_provider_map;
    std::optional<int> port;

    std::thread server_thread;
    std::mutex server_mutex;

    static httplib::Server::Handler create_handler(const std::unique_ptr<ResponseProvider>& provider) {
        return httplib::Server::Handler([&provider](const httplib::Request& req, httplib::Response& res) {
            if (!provider->get_response().has_value()) {
                return;
            }

            res.set_content(provider->get_response()->get_body().value(),
                            provider->get_response()->get_content_type()->c_str());
        });
    }
};

MockHttpServer::MockHttpServer() : impl(std::make_shared<MockHttpServerImpl>()) {
}

void MockHttpServer::start() {
    impl->start();
}

void MockHttpServer::stop() {
    impl->stop();
}

ResponseProvider& MockHttpServer::given(const sdk::http::HttpRequest& request) {
    return impl->given(request);
}

std::string MockHttpServer::uri() {
    return impl->uri();
}

}
