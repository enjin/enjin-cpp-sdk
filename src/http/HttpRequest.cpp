#include "enjinsdk/HttpRequest.hpp"

#include <utility>

namespace enjin::sdk::http {

HttpRequest HttpRequestBuilder::build() {
    return HttpRequest(m_method,
                       m_path_query_fragment,
                       m_body,
                       m_content_type);
}

HttpRequestBuilder& HttpRequestBuilder::method(const std::string& method) {
    m_method = method;
    return *this;
}

HttpRequestBuilder& HttpRequestBuilder::path_query_fragment(const std::string& path_query_fragment) {
    m_path_query_fragment = path_query_fragment;
    return *this;
}

HttpRequestBuilder& HttpRequestBuilder::body(const std::string& body) {
    m_body = body;
    return *this;
}

HttpRequestBuilder& HttpRequestBuilder::content_type(const std::string& content_type) {
    m_content_type = content_type;
    return *this;
}

HttpRequest::HttpRequest(std::string  method,
                         std::string  path_query_fragment,
                         std::string  body_data,
                         std::string  content_type) :
        method(std::move(method)),
        path_query_fragment(std::move(path_query_fragment)),
        body(std::move(body_data)),
        content_type(std::move(content_type)) {
}

std::string HttpRequest::get_method() const {
    return method;
}

std::string HttpRequest::get_path_query_fragment() const {
    return path_query_fragment;
}

std::string HttpRequest::get_body() const {
    return body;
}

std::string HttpRequest::get_content_type() const {
    return content_type;
}

bool HttpRequest::operator==(const HttpRequest& rhs) const {
    return method == rhs.method &&
           path_query_fragment == rhs.path_query_fragment &&
           body == rhs.body &&
           content_type == rhs.content_type;
}

bool HttpRequest::operator!=(const HttpRequest& rhs) const {
    return !(rhs == *this);
}

bool HttpRequest::operator<(const HttpRequest& rhs) const {
    if (method < rhs.method)
        return true;
    if (rhs.method < method)
        return false;
    if (path_query_fragment < rhs.path_query_fragment)
        return true;
    if (rhs.path_query_fragment < path_query_fragment)
        return false;
    if (body < rhs.body)
        return true;
    if (rhs.body < body)
        return false;
    return content_type < rhs.content_type;
}

bool HttpRequest::operator>(const HttpRequest& rhs) const {
    return rhs < *this;
}

bool HttpRequest::operator<=(const HttpRequest& rhs) const {
    return !(rhs < *this);
}

bool HttpRequest::operator>=(const HttpRequest& rhs) const {
    return !(*this < rhs);
}

}
