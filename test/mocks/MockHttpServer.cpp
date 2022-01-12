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
#include "enjinsdk/HttpHeaders.hpp"
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <utility>

namespace enjin::test::mocks {

void ResponseProvider::respond_with(sdk::http::HttpResponse response) {
    if (!response.get_body().has_value()) {
        throw std::runtime_error("Stub response does not have a body");
    } else if (!response.has_header(sdk::http::CONTENT_TYPE)) {
        throw std::runtime_error("Stub response does not have content-type header");
    }

    ResponseProvider::response = std::move(response);
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

    void next_message(std::function<void(const sdk::http::HttpRequest&)> handler) {
        std::lock_guard<std::mutex> guard(messages_mutex);
        message_handlers.emplace(std::move(handler));
    }

    ResponseProvider& given(const sdk::http::HttpRequest& request) {
        if (!request.get_path_query_fragment().has_value()) {
            throw std::runtime_error("Request does not have a set path query fragment");
        }
        if (!request.get_method().has_value()) {
            throw std::runtime_error("Request does not have a set HTTP method");
        }

        auto path_query_fragment = request.get_path_query_fragment().value();
        auto method = request.get_method().value();

        std::lock_guard<std::mutex> guard(server_mutex);

        response_provider_map[path_query_fragment] = std::make_unique<ResponseProvider>();
        auto& provider = response_provider_map[path_query_fragment];
        auto handler = create_handler(provider);

        switch (method) {
            case sdk::http::HttpMethod::GET:
                server.Get(path_query_fragment.c_str(), handler);
                break;
            case sdk::http::HttpMethod::POST:
                server.Post(path_query_fragment.c_str(), handler);
                break;
            case sdk::http::HttpMethod::PUT:
                server.Put(path_query_fragment.c_str(), handler);
                break;
            case sdk::http::HttpMethod::DEL:
                server.Delete(path_query_fragment.c_str(), handler);
                break;
            case sdk::http::HttpMethod::OPTIONS:
                server.Options(path_query_fragment.c_str(), handler);
                break;
            case sdk::http::HttpMethod::PATCH:
                server.Patch(path_query_fragment.c_str(), handler);
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
    std::optional<int> port;

    std::map<std::string, std::unique_ptr<ResponseProvider>> response_provider_map;
    std::queue<std::function<void(sdk::http::HttpRequest)>> message_handlers;

    // Threads
    std::thread server_thread;

    // Mutexes
    mutable std::mutex messages_mutex;
    mutable std::mutex server_mutex;

    httplib::Server::Handler create_handler(const std::unique_ptr<ResponseProvider>& provider) {
        return {[this, &provider](const httplib::Request& req, httplib::Response& res) {
            process_next_message(req);

            if (!provider->get_response().has_value()) {
                return;
            }

            res.status = provider->get_response()->get_code().value();
            res.set_content(provider->get_response()->get_body().value(),
                            provider->get_response()->get_header_value(sdk::http::CONTENT_TYPE)->c_str());
        }};
    }

    void process_next_message(const httplib::Request& req) {
        std::unique_lock<std::mutex> lock(messages_mutex);
        if (message_handlers.empty()) {
            return;
        }

        auto handler = message_handlers.front();
        message_handlers.pop();
        lock.unlock();

        auto request = sdk::http::HttpRequest()
                .set_method(convert_http_method(req.method))
                .set_path_query_fragment(req.path)
                .set_body(req.body);

        for (const auto&[k, v]: req.headers) {
            request.add_header(k, v);
        }

        handler(request);
    }

    static sdk::http::HttpMethod convert_http_method(const std::string& method) {
        if (method == "GET") {
            return sdk::http::HttpMethod::GET;
        } else if (method == "POST") {
            return sdk::http::HttpMethod::POST;
        } else if (method == "PUT") {
            return sdk::http::HttpMethod::PUT;
        } else if (method == "DELETE") {
            return sdk::http::HttpMethod::DEL;
        } else if (method == "OPTIONS") {
            return sdk::http::HttpMethod::OPTIONS;
        } else if (method == "PATCH") {
            return sdk::http::HttpMethod::PATCH;
        }

        throw std::runtime_error("Unsupported HTTP method conversion");
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

void MockHttpServer::next_message(std::function<void(const sdk::http::HttpRequest&)> handler) {
    impl->next_message(std::move(handler));
}

ResponseProvider& MockHttpServer::given(const sdk::http::HttpRequest& request) {
    return impl->given(request);
}

std::string MockHttpServer::uri() {
    return impl->uri();
}

}
