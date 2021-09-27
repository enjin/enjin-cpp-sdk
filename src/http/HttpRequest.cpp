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

#include "enjinsdk/HttpRequest.hpp"

#include <stdexcept>
#include <utility>

namespace enjin::sdk::http {

HttpRequest HttpRequestBuilder::build() {
    if (!m_method.has_value()) {
        throw std::runtime_error("No defined method for built request");
    }

    return HttpRequest(m_method.value(),
                       m_path_query_fragment,
                       m_body,
                       m_content_type,
                       headers);
}

HttpRequestBuilder& HttpRequestBuilder::method(HttpMethod method) {
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

HttpRequestBuilder& HttpRequestBuilder::add_header(const std::string& name, const std::string& value) {
    headers.emplace(name, value);
    return *this;
}

HttpRequest::HttpRequest(HttpMethod method,
                         std::string path_query_fragment,
                         std::string body_data,
                         std::string content_type,
                         std::map<std::string, std::string> headers) :
        method(method),
        path_query_fragment(std::move(path_query_fragment)),
        body(std::move(body_data)),
        content_type(std::move(content_type)),
        headers(std::move(headers)) {
}

HttpMethod HttpRequest::get_method() const {
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

const std::map<std::string, std::string>& HttpRequest::get_headers() const {
    return headers;
}

std::string HttpRequest::get_header_value(const std::string& name) const {
    return headers.at(name);
}

bool HttpRequest::has_header(const std::string& name) const noexcept {
    return headers.find(name) != headers.end();
}

bool HttpRequest::operator==(const HttpRequest& rhs) const {
    return method == rhs.method &&
           path_query_fragment == rhs.path_query_fragment &&
           body == rhs.body &&
           content_type == rhs.content_type &&
           headers == rhs.headers;
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
