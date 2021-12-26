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

HttpRequest& HttpRequest::set_method(HttpMethod method) {
    HttpRequest::method = method;
    return *this;
}

HttpRequest& HttpRequest::set_path_query_fragment(std::string path_query_fragment) {
    HttpRequest::path_query_fragment = std::move(path_query_fragment);
    return *this;
}

HttpRequest& HttpRequest::set_body(std::string body) {
    HttpRequest::body = std::move(body);
    return *this;
}

HttpRequest& HttpRequest::set_content_type(std::string content_type) {
    HttpRequest::content_type = std::move(content_type);
    return *this;
}

HttpRequest& HttpRequest::add_header(std::string name, std::string value) {
    headers.emplace(std::move(name), std::move(value));
    return *this;
}

const std::optional<HttpMethod>& HttpRequest::get_method() const {
    return method;
}

const std::optional<std::string>& HttpRequest::get_path_query_fragment() const {
    return path_query_fragment;
}

const std::optional<std::string>& HttpRequest::get_body() const {
    return body;
}

const std::optional<std::string>& HttpRequest::get_content_type() const {
    return content_type;
}

const std::map<std::string, std::string>& HttpRequest::get_headers() const {
    return headers;
}

std::optional<std::string> HttpRequest::get_header_value(const std::string& name) const {
    return has_header(name)
           ? std::optional<std::string>(headers.at(name))
           : std::optional<std::string>();
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
