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

#include "EnumUtils.hpp"
#include "httplib.h"
#include "enjinsdk_utils/StringUtils.hpp"
#include <chrono>
#include <iterator>
#include <map>
#include <mutex>
#include <sstream>
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
    }

    void stop() override {
        if (!is_open()) {
            return;
        }

        http_client->stop();
        open = false;
    }

    std::future<HttpResponse> send_request(HttpRequest request) override {
        return std::async([this, request] {
            validate_request_method(request);
            validate_request_path_query_fragment(request);
            validate_request_content_type(request);
            validate_request_body(request);

            auto req = httplib::Request();
            req.path = request.get_path_query_fragment().value();
            req.method = utils::serialize_http_method(request.get_method().value());
            req.headers = create_headers(request);
            req.body = request.get_body().value();

            log_request(req);

            const auto begin = std::chrono::high_resolution_clock::now();
            auto res = http_client->send(req);
            const auto end = std::chrono::high_resolution_clock::now();

            log_result(req, res, std::chrono::duration_cast<std::chrono::milliseconds>(end - begin));

            if (!res) {
                throw std::runtime_error(error_result_2_string(res));
            }

            auto builder = HttpResponse::builder();
            for (auto&[key, value]: res->headers) {
                builder.add_header(key, value);
            }

            return builder.code(res->status)
                          .body(res->body)
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

    bool open = false;
    std::map<std::string, std::string> default_headers;
    HttpLogLevel log_level = HttpLogLevel::None;

    std::unique_ptr<httplib::Client> http_client;
    std::shared_ptr<utils::LoggerProvider> logger_provider;

    // Mutexes
    mutable std::mutex default_headers_mutex;
    mutable std::mutex logging_mutex;

    httplib::Headers create_headers(const HttpRequest& request) {
        httplib::Headers headers;

        std::unique_lock<std::mutex> default_headers_lock(default_headers_mutex);
        for (const auto& entry: default_headers) {
            headers.emplace(entry.first, entry.second);
        }
        default_headers_lock.unlock();

        for (const auto& entry: request.get_headers()) {
            headers.emplace(entry.first, entry.second);
        }

        return headers;
    }

    void log_error(const std::string& message) {
        std::lock_guard<std::mutex> guard(logging_mutex);
        if (logger_provider != nullptr) {
            logger_provider->log(utils::LogLevel::ERR, message);
        }
    }

    void log_request(const httplib::Request& req) {
        std::lock_guard<std::mutex> guard(logging_mutex);
        if (log_level == HttpLogLevel::None || logger_provider == nullptr) {
            return;
        }

        std::stringstream ss;

        const auto method = enjin::utils::to_upper(req.method);
        const auto uri = base_uri + req.path;
        const auto content_length = req.body.size();

        // Line
        if (log_level == HttpLogLevel::Basic) {
            ss << "--> " << method << " " << uri << " (" << content_length << "-byte body)\n";
            logger_provider->log(ss.str());
            return;
        }

        ss << "--> " << method << " " << uri << "\n";

        // Headers
        for (const auto&[k, v]: req.headers) {
            ss << k << ": " << v << "\n";
        }

        if (log_level == HttpLogLevel::Headers) {
            ss << "<-- END " << method << "\n";
            logger_provider->log(ss.str());
            return;
        }

        // Body
        ss << "\n" // Line break between headers and body
           << req.body << "\n"
           << "<-- END " << method << " (" << content_length << "-byte body)\n";
        logger_provider->log(ss.str());
    }

    void log_result(const httplib::Request& req, const httplib::Result& res, std::chrono::milliseconds rtt) {
        std::lock_guard<std::mutex> guard(logging_mutex);
        if (log_level == HttpLogLevel::None || logger_provider == nullptr) {
            return;
        }

        std::stringstream ss;

        const auto status = res->status;
        const auto uri = base_uri + req.path;

        // Line
        ss << "<-- " << status << " " << uri << " (" << rtt.count() << "ms)\n";

        if (log_level == HttpLogLevel::Basic) {
            logger_provider->log(ss.str());
            return;
        }

        // Headers
        for (const auto&[k, v]: res->headers) {
            ss << k << ": " << v << "\n";
        }

        if (log_level == HttpLogLevel::Headers) {
            ss << "<-- END HTTP\n";
            logger_provider->log(ss.str());
            return;
        }

        // Body
        ss << "\n"
           << res->body << "\n"
           << "<-- END HTTP\n";
        logger_provider->log(ss.str());
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
        if (req.get_method().has_value() && req.get_method().value() == HttpMethod::Post) {
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
    return impl->send_request(request);
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
