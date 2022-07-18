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

#ifndef ENJINCPPSDK_HTTPREQUEST_HPP
#define ENJINCPPSDK_HTTPREQUEST_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/HttpMethod.hpp"
#include <optional>
#include <map>
#include <string>

namespace enjin::sdk::http {

/// \brief Container class for a HTTP request.
class ENJINSDK_EXPORT HttpRequest {
public:
    /// \brief Default constructor.
    HttpRequest() = default;

    /// \brief Default destructor.
    ~HttpRequest() = default;

    /// \brief Sets the HTTP method for this request.
    /// \param method The HTTP method.
    /// \return This request for chaining.
    HttpRequest& set_method(HttpMethod method);

    /// \brief Sets the path query fragment for this request.
    /// \param path_query_fragment The path query fragment.
    /// \return This request for chaining.
    HttpRequest& set_path_query_fragment(std::string path_query_fragment);

    /// \brief Sets the body data for this request.
    /// \param body The request body.
    /// \return This request for chaining.
    HttpRequest& set_body(std::string body);

    /// \brief Sets the content-type header for this request.
    /// \param content_type The content type.
    /// \return This request for chaining.
    HttpRequest& set_content_type(std::string content_type);

    /// \brief Adds a header for this request.
    /// \param name The header name.
    /// \param value The header value.
    /// \return This request for chaining.
    HttpRequest& add_header(std::string name, std::string value);

    /// \brief Returns the HTTP method of this request.
    /// \return The HTTP method.
    [[nodiscard]] const std::optional<HttpMethod>& get_method() const;

    /// \brief Returns the path query fragment of this request.
    /// \return The path query fragment.
    [[nodiscard]] const std::optional<std::string>& get_path_query_fragment() const;

    /// \brief Returns the body of this request.
    /// \return The request body.
    [[nodiscard]] const std::optional<std::string>& get_body() const;

    /// \brief Returns the content-type header of this request.
    /// \return An optional containing the content-type value if one exists.
    [[nodiscard]] std::optional<std::string> get_content_type() const;

    /// \brief Returns the map for the HTTP headers.
    /// \return The headers.
    [[nodiscard]] const std::map<std::string, std::string>& get_headers() const;

    /// \brief Returns the value for the header.
    /// \param name The header name.
    /// \return An optional containing the header value if one exists.
    [[nodiscard]] std::optional<std::string> get_header_value(const std::string& name) const;

    /// \brief Determines if a value exists for the provided header name.
    /// \param name The header name.
    /// \return Whether a value exists.
    [[nodiscard]] bool has_header(const std::string& name) const noexcept;

    bool operator==(const HttpRequest& rhs) const;

    bool operator!=(const HttpRequest& rhs) const;

    bool operator<(const HttpRequest& rhs) const;

    bool operator>(const HttpRequest& rhs) const;

    bool operator<=(const HttpRequest& rhs) const;

    bool operator>=(const HttpRequest& rhs) const;

private:
    std::optional<HttpMethod> method;
    std::optional<std::string> path_query_fragment;
    std::optional<std::string> body;
    std::map<std::string, std::string> headers;
};

}

#endif //ENJINCPPSDK_HTTPREQUEST_HPP
