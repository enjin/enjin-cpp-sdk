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

#include "enjinsdk/HttpResponse.hpp"

#include "rapidjson/document.h"
#include <utility>

namespace enjin::sdk::http {

HttpResponse::HttpResponse(std::optional<unsigned short> code,
                           std::optional<std::string> body,
                           std::map<std::string, std::string> headers)
        : code(code),
          body(std::move(body)),
          headers(std::move(headers)) {
}

bool HttpResponse::is_success() const {
    return code.has_value() && code.value() >= 200 && code.value() < 300;
}

bool HttpResponse::is_empty() const {
    if (!body.has_value()) {
        return true;
    }

    rapidjson::Document document;
    document.Parse(body.value().c_str());

    return body.value().empty() || (document.IsObject() && document.ObjectEmpty());
}

const std::optional<unsigned short>& HttpResponse::get_code() const {
    return code;
}

const std::optional<std::string>& HttpResponse::get_body() const {
    return body;
}

const std::map<std::string, std::string>& HttpResponse::get_headers() const {
    return headers;
}

std::optional<std::string> HttpResponse::get_header_value(const std::string& name) const {
    return has_header(name)
           ? std::optional<std::string>(headers.at(name))
           : std::optional<std::string>();
}

bool HttpResponse::has_header(const std::string& name) const noexcept {
    return headers.find(name) != headers.end();
}

bool HttpResponse::operator==(const HttpResponse& rhs) const {
    return code == rhs.code &&
           body == rhs.body &&
           headers == rhs.headers;
}

bool HttpResponse::operator!=(const HttpResponse& rhs) const {
    return !(rhs == *this);
}

HttpResponse::HttpResponseBuilder HttpResponse::builder() {
    return {};
}

HttpResponse HttpResponse::HttpResponseBuilder::build() {
    return {m_code, std::move(m_body), std::move(headers)};
}

HttpResponse::HttpResponseBuilder& HttpResponse::HttpResponseBuilder::code(unsigned short code) {
    m_code = code;
    return *this;
}

HttpResponse::HttpResponseBuilder& HttpResponse::HttpResponseBuilder::body(std::string body) {
    m_body = std::move(body);
    return *this;
}

HttpResponse::HttpResponseBuilder& HttpResponse::HttpResponseBuilder::add_header(std::string name, std::string value) {
    headers.emplace(std::move(name), std::move(value));
    return *this;
}

}
