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

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "HttpClient.hpp"

#include "httplib.h"
#include "enjinsdk/HttpHeaders.hpp"
#include <iterator>
#include <map>
#include <mutex>
#include <stdexcept>
#include <utility>

namespace enjin::sdk::http {

class HttpClient::Impl : public IHttpClient {
public:
    Impl() = delete;

    explicit Impl(std::string base_uri) : base_uri(std::move(base_uri)) {
    }

    ~Impl() override {
        Impl::stop();
    }

    void start() override {
        if (is_open()) {
            return;
        }

        http_client = std::make_unique<httplib::Client>(base_uri.c_str());
        http_client->set_follow_location(true);
        http_client->set_keep_alive(true);
        open = true;

        if (logger_provider != nullptr) {
            http_client->set_logger([this](const httplib::Request& req, const httplib::Response& res) {
                std::stringstream ss;
                ss << "\n"
                   << request_2_string(req) << ",\n"
                   << response_2_string(res);
                logger_provider->log(utils::LogLevel::INFO, ss.str());
            });
        }
    }

    void stop() override {
        if (!is_open()) {
            return;
        }

        http_client->stop();
        open = false;
    }

    std::future<HttpResponse> send_request(HttpRequest request) override {
        return std::async([this, request = std::move(request)] {
            validate_request_method(request);
            validate_request_path_query_fragment(request);
            validate_request_content_type(request);
            validate_request_body(request);

            // Compiles and formats headers for cpp-httplib usage
            auto headers = create_headers(request);
            auto content_type = headers.extract(CONTENT_TYPE).mapped();

            auto result = http_client->Post(request.get_path_query_fragment().value().c_str(),
                                            headers,
                                            request.get_body().value(),
                                            content_type.c_str());
            if (!result) {
                const std::string message(error_result_2_string(result));
                log_error(message);
                throw std::runtime_error(message);
            }

            auto builder = HttpResponse::builder();
            for (auto&[key, value]: result->headers) {
                builder.add_header(key, value);
            }

            return builder.code(result->status)
                          .body(result->body)
                          .build();
        });
    }

    [[nodiscard]] const std::string& get_base_uri() const {
        return base_uri;
    }

    [[nodiscard]] bool is_open() const override {
        return open;
    }

    void set_default_request_header(std::string key, std::string value) override {
        std::lock_guard<std::mutex> guard(default_headers_mutex);
        default_headers.emplace(std::move(key), std::move(value));
    }

    void set_logger(HttpLogLevel level, std::shared_ptr<utils::LoggerProvider> logger_provider) override {
        std::lock_guard<std::mutex> guard(logging_mutex);
        log_level = level;
        Impl::logger_provider = std::move(logger_provider);
    }

private:
    const std::string base_uri;

    HttpLogLevel log_level = HttpLogLevel::NONE;
    bool open = false;
    std::map<std::string, std::string> default_headers;

    std::unique_ptr<httplib::Client> http_client;
    std::shared_ptr<utils::LoggerProvider> logger_provider;

    // Mutexes
    mutable std::mutex default_headers_mutex;
    mutable std::mutex logging_mutex;

    httplib::Headers create_headers(const HttpRequest& request) {
        httplib::Headers headers;

        std::unique_lock<std::mutex> default_headers_lock(default_headers_mutex);
        for (const auto& entry : default_headers) {
            headers.emplace(entry.first, entry.second);
        }
        default_headers_lock.unlock();

        for (const auto& entry: request.get_headers()) {
            headers.emplace(entry.first, entry.second);
        }

        return headers;
    }

    void log_error(const std::string& message) {
        if (logger_provider != nullptr) {
            logger_provider->log(utils::LogLevel::ERR, message);
        }
    }

    std::string request_2_string(const httplib::Request& req) {
        std::stringstream ss;
        ss << "Request Method: " << req.method << ",\n"
           << "Request URL: " << base_uri << req.path << ",\n"
           << "Request Body: " << req.body << ",\n"
           << "Request Headers: " << headers_2_string(req.headers);
        return ss.str();
    }

    void validate_request_body(const HttpRequest& req) {
        if (req.get_body().has_value()) {
            return;
        }

        const std::string message("Request does not have a body");
        log_error(message);
        throw std::runtime_error(message);
    }

    void validate_request_content_type(const HttpRequest& req) {
        if (req.get_content_type().has_value()) {
            return;
        }

        const std::string message("Request does not have a content-type header");
        log_error(message);
        throw std::runtime_error(message);
    }

    void validate_request_method(const HttpRequest& req) {
        if (req.get_method().has_value() && req.get_method().value() == HttpMethod::POST) {
            return;
        }

        const std::string message("HTTP method for request is not 'POST'");
        log_error(message);
        throw std::runtime_error(message);
    }

    void validate_request_path_query_fragment(const HttpRequest& req) {
        if (req.get_path_query_fragment().has_value()) {
            return;
        }

        const std::string message("Request does not have a path query fragment");
        log_error(message);
        throw std::runtime_error(message);
    }

    static std::string error_enum_2_string(const httplib::Error value) {
        switch (value) {
            case httplib::Error::Connection:
                return "Connection";
            case httplib::Error::BindIPAddress:
                return "BindIPAddress";
            case httplib::Error::Read:
                return "Read";
            case httplib::Error::Write:
                return "Write";
            case httplib::Error::ExceedRedirectCount:
                return "ExceedRedirectCount";
            case httplib::Error::Canceled:
                return "Canceled";
            case httplib::Error::SSLConnection:
                return "SSLConnection";
            case httplib::Error::SSLLoadingCerts:
                return "SSLLoadingCerts";
            case httplib::Error::SSLServerVerification:
                return "SSLServerVerification";
            case httplib::Error::UnsupportedMultipartBoundaryChars:
                return "UnsupportedMultipartBoundaryChars";
            default:
                return "Unknown";
        }
    }

    static std::string error_result_2_string(const httplib::Result& result) {
        std::stringstream ss;
        ss << "HTTP client encountered an error with designation '" << error_enum_2_string(result.error()) << "'";
        return ss.str();
    }

    static std::string headers_2_string(const httplib::Headers& headers) {
        if (headers.empty()) {
            return "{}";
        }

        std::stringstream ss;

        ss << "{";

        const auto& last = std::prev(headers.end());
        auto iter = headers.begin();
        while (iter != headers.end()) {
            ss << "'" << iter->first << "': '" << iter->second << "'";

            // Adds separator if not the last entry
            if (iter != last) {
                ss << ", ";
            }

            iter = std::next(iter);
        }

        ss << "}";

        return ss.str();
    }

    static std::string response_2_string(const httplib::Response& res) {
        std::stringstream ss;
        ss << "Response Code: " << res.status << ",\n"
           << "Response Headers: " << headers_2_string(res.headers) << ",\n"
           << "Response Body Text: " << res.body;
        return ss.str();
    }
};

HttpClient::HttpClient(std::string base_uri) : impl(new Impl(std::move(base_uri))) {
}

HttpClient::~HttpClient() {
    delete impl;
}

void HttpClient::start() {
    impl->start();
}

void HttpClient::stop() {
    impl->stop();
}

std::future<HttpResponse> HttpClient::send_request(HttpRequest request) {
    return impl->send_request(std::move(request));
}

const std::string& HttpClient::get_base_uri() const {
    return impl->get_base_uri();
}

bool HttpClient::is_open() const {
    return impl->is_open();
}

void HttpClient::set_default_request_header(std::string key, std::string value) {
    impl->set_default_request_header(std::move(key), std::move(value));
}

void HttpClient::set_logger(HttpLogLevel level, std::shared_ptr<utils::LoggerProvider> logger_provider) {
    impl->set_logger(level, std::move(logger_provider));
}

}
