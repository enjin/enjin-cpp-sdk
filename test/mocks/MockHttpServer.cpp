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

#include "EnumUtils.hpp"
#include "httplib.h"
#include "enjinsdk/HttpHeaders.hpp"
#include "enjinsdk_utils/StringUtils.hpp"
#include <memory>
#include <mutex>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <utility>

namespace enjin::test::mocks {

// region Request

Request& Request::using_delete() {
    m_method = sdk::http::HttpMethod::DEL;
    return *this;
}

Request& Request::using_get() {
    m_method = sdk::http::HttpMethod::GET;
    return *this;
}

Request& Request::using_post() {
    m_method = sdk::http::HttpMethod::POST;
    return *this;
}

Request& Request::using_put() {
    m_method = sdk::http::HttpMethod::PUT;
    return *this;
}

Request& Request::with_body(std::string body) {
    m_body = std::move(body);
    return *this;
}

Request& Request::with_path(std::string path) {
    m_path = std::move(path);
    return *this;
}

const std::optional<std::string>& Request::get_body() const {
    return m_body;
}

const std::optional<std::string>& Request::get_path() const {
    return m_path;
}

const std::optional<sdk::http::HttpMethod>& Request::get_method() const {
    return m_method;
}

bool Request::operator==(const Request& rhs) const {
    return m_path == rhs.m_path &&
           m_method == rhs.m_method;
}

bool Request::operator!=(const Request& rhs) const {
    return !(rhs == *this);
}

bool Request::operator<(const Request& rhs) const {
    if (m_path < rhs.m_path)
        return true;
    if (rhs.m_path < m_path)
        return false;
    return m_method < rhs.m_method;
}

bool Request::operator>(const Request& rhs) const {
    return rhs < *this;
}

bool Request::operator<=(const Request& rhs) const {
    return !(rhs < *this);
}

bool Request::operator>=(const Request& rhs) const {
    return !(*this < rhs);
}

Request Request::create() {
    return {};
}

// endregion Request

// region Response

Response& Response::with_body(std::string body) {
    m_body = std::move(body);
    return *this;
}

Response& Response::with_header(std::string name, std::string value) {
    m_headers.emplace(std::move(name), std::move(value));
    return *this;
}

Response& Response::with_status_code(int code) {
    m_status_code = code;
    return *this;
}

Response& Response::with_success() {
    m_status_code = 200;
    return *this;
}

const std::optional<std::string>& Response::get_body() const {
    return m_body;
}

const std::map<std::string, std::string>& Response::get_headers() const {
    return m_headers;
}

const std::optional<int>& Response::get_status_code() const {
    return m_status_code;
}

Response Response::create() {
    return {};
}

// endregion Response

// region RequestMessage

const std::string& RequestMessage::get_body() const {
    return body;
}

const std::map<std::string, std::string>& RequestMessage::get_headers() const {
    return headers;
}

const std::string& RequestMessage::get_method() const {
    return method;
}

const std::string& RequestMessage::get_path() const {
    return path;
}

RequestMessage& RequestMessage::add_header(std::string name, std::string value) {
    headers.emplace(std::move(name), std::move(value));
    return *this;
}

RequestMessage& RequestMessage::set_body(std::string value) {
    body = std::move(value);
    return *this;
}

RequestMessage& RequestMessage::set_method(std::string value) {
    method = std::move(value);
    return *this;
}

RequestMessage& RequestMessage::set_path(std::string value) {
    path = std::move(value);
    return *this;
}

// endregion RequestMessage

// region ResponseMessage

const std::string& ResponseMessage::get_body() const {
    return body;
}

const std::map<std::string, std::string>& ResponseMessage::get_headers() const {
    return headers;
}

int ResponseMessage::get_status_code() const {
    return status_code;
}

ResponseMessage& ResponseMessage::add_header(std::string name, std::string value) {
    headers.emplace(std::move(name), std::move(value));
    return *this;
}

ResponseMessage& ResponseMessage::set_body(std::string value) {
    body = std::move(value);
    return *this;
}

ResponseMessage& ResponseMessage::set_status_code(int value) {
    status_code = value;
    return *this;
}

// endregion ResponseMessage

// region ResponseProvider

void ResponseProvider::respond_with(Response response) {
    m_response = std::move(response);
}

const std::optional<Response>& ResponseProvider::get_response() const {
    return m_response;
}

// endregion ResponseProvider

// region LogEntry

const std::optional<RequestMessage>& LogEntry::get_request_message() const {
    return request;
}

const std::optional<ResponseMessage>& LogEntry::get_response_message() const {
    return response;
}

void LogEntry::set_request_message(RequestMessage message) {
    request = std::move(message);
}

void LogEntry::set_response_message(ResponseMessage message) {
    response = std::move(message);
}

// endregion LogEntry

// region MockHttpServer implementation

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

    ResponseProvider& given(const Request& request) {
        const auto& path_optional = request.get_path();
        if (!path_optional.has_value()) {
            throw std::runtime_error("Request does not have a set path query fragment");
        }

        const auto& method_optional = request.get_method();
        if (!method_optional.has_value()) {
            throw std::runtime_error("Request does not have a set HTTP method");
        }

        const auto& path = path_optional.value();
        auto method = method_optional.value();

        std::lock_guard<std::mutex> guard(server_mutex);

        response_provider_map[path] = std::unique_ptr<ResponseProvider>(new ResponseProvider());
        auto& provider = response_provider_map[path];
        auto handler = create_handler(provider);

        switch (method) {
            case sdk::http::HttpMethod::GET:
                server.Get(path.c_str(), handler);
                break;
            case sdk::http::HttpMethod::POST:
                server.Post(path.c_str(), handler);
                break;
            case sdk::http::HttpMethod::PUT:
                server.Put(path.c_str(), handler);
                break;
            case sdk::http::HttpMethod::DEL:
                server.Delete(path.c_str(), handler);
                break;
            case sdk::http::HttpMethod::OPTIONS:
                server.Options(path.c_str(), handler);
                break;
            case sdk::http::HttpMethod::PATCH:
                server.Patch(path.c_str(), handler);
                break;
            default:
                throw std::runtime_error("Unsupported HTTP method");
        }

        log_entries.try_emplace(request, std::vector<LogEntry>());

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

    std::vector<LogEntry> find_received_requests(const Request& request) const {
        auto iter = log_entries.find(request);
        if (iter != log_entries.end()) {
            return iter->second;
        }

        return {};
    }

private:
    httplib::Server server;
    std::optional<int> port;

    std::map<std::string, std::unique_ptr<ResponseProvider>> response_provider_map;
    std::queue<std::function<void(sdk::http::HttpRequest)>> message_handlers;
    std::map<Request, std::vector<LogEntry>> log_entries;

    // Threads
    std::thread server_thread;

    // Mutexes
    mutable std::mutex log_entries_mutex;
    mutable std::mutex messages_mutex;
    mutable std::mutex server_mutex;

    static constexpr char DEFAULT_CONTENT_TYPE[] = "text/plain; charset=utf-8";

    httplib::Server::Handler create_handler(const std::unique_ptr<ResponseProvider>& provider) {
        return {[this, &provider](const httplib::Request& req, httplib::Response& res) {
            auto log_entry = LogEntry();
            log_entry.set_request_message(create_request_message(req));

            if (provider->get_response().has_value()) {
                res.status = provider->get_response()->get_status_code().value();

                auto& headers = provider->get_response()->get_headers();
                auto iter = headers.find(sdk::http::CONTENT_TYPE);
                if (iter == headers.end()) {
                    res.set_content(provider->get_response()->get_body().value(), DEFAULT_CONTENT_TYPE);
                } else {
                    res.set_content(provider->get_response()->get_body().value(), iter->second.c_str());
                }

                log_entry.set_response_message(create_response_message(res));
            }

            std::unique_lock<std::mutex> lock(log_entries_mutex);
            log_entries.at(convert_request(req)).push_back(std::move(log_entry));
            lock.unlock();

            process_next_message(req);
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
        return sdk::utils::deserialize_http_method(utils::to_upper(method));
    }

    static Request convert_request(const httplib::Request& req) {
        auto new_req = Request::create()
                .with_path(req.path)
                .with_body(req.body);

        auto method = convert_http_method(req.method);
        switch (method) {
            case sdk::http::HttpMethod::GET:
                new_req.using_get();
                break;
            case sdk::http::HttpMethod::POST:
                new_req.using_post();
                break;
            case sdk::http::HttpMethod::PUT:
                new_req.using_put();
                break;
            case sdk::http::HttpMethod::DEL:
                new_req.using_delete();
                break;
            default:
                throw std::runtime_error("Unsupported HTTP method");
        }

        return new_req;
    }

    static RequestMessage create_request_message(const httplib::Request& req) {
        auto msg = RequestMessage()
                .set_path(req.path)
                .set_method(req.method)
                .set_body(req.body);

        for (const auto& [k, v] : req.headers) {
            msg.add_header(k, v);
        }

        return msg;
    }

    static ResponseMessage create_response_message(const httplib::Response& res) {
        auto msg = ResponseMessage()
                .set_status_code(res.status)
                .set_body(res.body);

        for (const auto& [k, v] : res.headers) {
            msg.add_header(k, v);
        }

        return msg;
    }
};

// endregion MockHttpServer implementation

// region MockHttpServer

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

ResponseProvider& MockHttpServer::given(const Request& request) {
    return impl->given(request);
}

std::string MockHttpServer::uri() {
    return impl->uri();
}

std::vector<LogEntry> MockHttpServer::find_received_requests(const Request& request) const {
    return impl->find_received_requests(request);
}

// endregion MockHttpServer

}
