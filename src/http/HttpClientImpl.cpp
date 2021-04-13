#include "HttpClientImpl.hpp"

#include <iterator>
#include <stdexcept>
#include <utility>

namespace enjin::sdk::http {

std::string headers_2_string(const httplib::Headers& headers) {
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

std::string request_2_string(const httplib::Request& req, const HttpClientImpl& client) {
    std::stringstream ss;
    ss << "Request Method: " << req.method << ",\n"
       << "Request URL: " << client.get_base_uri() << req.path << ",\n"
       << "Request Body: " << req.body << ",\n"
       << "Request Headers: " << headers_2_string(req.headers);
    return ss.str();
}

std::string response_2_string(const httplib::Response& res, const HttpClientImpl&) {
    std::stringstream ss;
    ss << "Response Code: " << res.status << ",\n"
       << "Response Headers: " << headers_2_string(res.headers) << ",\n"
       << "Response Body Text: " << res.body;
    return ss.str();
}

std::string error_result_2_string(const httplib::Result& result) {
    std::stringstream ss;
    ss << "Result unsuccessful (Code: " << result->status << ", Error: '";

    switch (result.error()) {
        case httplib::Error::Connection:
            ss << "Connection";
            break;
        case httplib::Error::BindIPAddress:
            ss << "BindIPAddress";
            break;
        case httplib::Error::Read:
            ss << "Read";
            break;
        case httplib::Error::Write:
            ss << "Write";
            break;
        case httplib::Error::ExceedRedirectCount:
            ss << "ExceedRedirectCount";
            break;
        case httplib::Error::Canceled:
            ss << "Canceled";
            break;
        case httplib::Error::SSLConnection:
            ss << "SSLConnection";
            break;
        case httplib::Error::SSLLoadingCerts:
            ss << "SSLLoadingCerts";
            break;
        case httplib::Error::SSLServerVerification:
            ss << "SSLServerVerification";
            break;
        case httplib::Error::UnsupportedMultipartBoundaryChars:
            ss << "UnsupportedMultipartBoundaryChars";
            break;
        default:
            ss << "Unknown";
            break;
    }

    ss << "', Reason: '" << result->reason << "')";

    return ss.str();
}

HttpClientImpl::HttpClientImpl(std::string base_uri, std::shared_ptr<utils::Logger> logger)
        : base_uri(std::move(base_uri)),
          logger(std::move(logger)) {
}

HttpClientImpl::~HttpClientImpl() {
    stop();
}

void HttpClientImpl::start() {
    if (is_open()) {
        return;
    }

    http_client = std::make_unique<httplib::Client>(base_uri.c_str());
    http_client->set_follow_location(true);
    http_client->set_keep_alive(true);
    open = true;

    if (logger != nullptr) {
        http_client->set_logger([this](const httplib::Request& req, const httplib::Response& res) {
            std::stringstream ss;
            ss << "\n"
               << request_2_string(req, *this) << ",\n"
               << response_2_string(res, *this);
            logger->log(utils::LogLevel::INFO, ss.str());
        });
    }
}

void HttpClientImpl::stop() {
    if (!is_open()) {
        return;
    }

    http_client->stop();
    open = false;
}

std::future<HttpResponse> HttpClientImpl::send_request(const HttpRequest& request) {
    return std::async([this, request] {
        if (request.get_method() != HttpMethod::Post) {
            const std::string message("HTTP method for request is not 'POST'");
            log_error(message);
            throw std::runtime_error(message);
        }

        auto result = http_client->Post(request.get_path_query_fragment().c_str(),
                                        create_headers(request),
                                        request.get_body(),
                                        request.get_content_type().c_str());
        if (result) {
            return HttpResponseBuilder()
                    .code(result->status)
                    .body(result->body)
                    .content_type(result->get_header_value("Content-Type"))
                    .build();
        } else {
            const std::string message(error_result_2_string(result));
            log_error(message);
            throw std::runtime_error(message);
        }
    });
}

void HttpClientImpl::log_error(const std::string& message) {
    if (logger != nullptr) {
        logger->log(utils::LogLevel::SEVERE, message);
    }
}

const std::string& HttpClientImpl::get_base_uri() const {
    return base_uri;
}

bool HttpClientImpl::is_open() const {
    return open;
}

httplib::Headers HttpClientImpl::create_headers(const HttpRequest& request) {
    httplib::Headers headers;

    for (const auto& entry : request.get_headers()) {
        headers.emplace(entry.first, entry.second);
    }

    return headers;
}

}
