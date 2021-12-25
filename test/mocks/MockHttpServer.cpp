/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MockHttpServer.hpp"

#include "httplib.h"
#include <map>
#include <memory>
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

class MockHttpServer::Impl {
public:
    Impl() {
        if (!server.set_mount_point("/", "./")) {
            throw std::runtime_error("The base directory does not exist");
        } else if (!server.is_valid()) {
            throw std::runtime_error("Server is not valid");
        }
    }

    ~Impl() {
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

        switch (request.get_method()) {
            case sdk::http::HttpMethod::GET:
                server.Get(request.get_path_query_fragment().c_str(), handler);
                break;
            case sdk::http::HttpMethod::POST:
                server.Post(request.get_path_query_fragment().c_str(), handler);
                break;
            case sdk::http::HttpMethod::PUT:
                server.Put(request.get_path_query_fragment().c_str(), handler);
                break;
            case sdk::http::HttpMethod::DEL:
                server.Delete(request.get_path_query_fragment().c_str(), handler);
                break;
            case sdk::http::HttpMethod::OPTIONS:
                server.Options(request.get_path_query_fragment().c_str(), handler);
                break;
            case sdk::http::HttpMethod::PATCH:
                server.Patch(request.get_path_query_fragment().c_str(), handler);
                break;
            default:
                throw std::runtime_error("Unsupported HTTP method");
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

            res.status = provider->get_response()->get_code().value();
            res.set_content(provider->get_response()->get_body().value(),
                            provider->get_response()->get_content_type()->c_str());
        });
    }
};

MockHttpServer::MockHttpServer() : impl(new Impl()) {
}

MockHttpServer::~MockHttpServer() {
    delete impl;
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
