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
    class HttpRequestBuilder;

    HttpRequest() = delete;

    /// \brief Default destructor.
    ~HttpRequest() = default;

    /// \brief Returns the HTTP method of this request.
    /// \return The HTTP method.
    [[nodiscard]] HttpMethod get_method() const;

    /// \brief Returns the path query fragment of this request.
    /// \return The path query fragment.
    [[nodiscard]] std::string get_path_query_fragment() const;

    /// \brief Returns the body of this request.
    /// \return The request body.
    [[nodiscard]] std::string get_body() const;

    /// \brief Returns the content type header of this request.
    /// \return The content type.
    [[nodiscard]] std::string get_content_type() const;

    /// \brief Returns the map for the HTTP headers.
    /// \return The headers.
    [[nodiscard]] const std::map<std::string, std::string>& get_headers() const;

    /// \brief Returns the value for the header.
    /// \param name The header name.
    /// \return The header value.
    /// \throws out_of_range If no value is mapped for the header.
    [[nodiscard]] std::string get_header_value(const std::string& name) const;

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

    /// \brief Creates a builder for this class.
    /// \return The builder.
    [[nodiscard]] static HttpRequestBuilder builder();

    /// \brief Builder class for HttpRequest.
    class ENJINSDK_EXPORT HttpRequestBuilder {
    public:
        /// \brief Default destructor.
        ~HttpRequestBuilder() = default;

        /// \brief Builds the request.
        /// \return The built request.
        /// \throws runtime_error If no HTTP method was set.
        [[nodiscard]] HttpRequest build();

        /// \brief Sets the HTTP method the request will be built with.
        /// \param method The HTTP method.
        /// \return This builder for chaining.
        HttpRequestBuilder& method(HttpMethod method);

        /// \brief Sets the path query fragment the request will be built with.
        /// \param path_query_fragment The path query fragment.
        /// \return This builder for chaining.
        HttpRequestBuilder& path_query_fragment(std::string path_query_fragment);

        /// \brief Sets the body data the request will be built with.
        /// \param body The request body.
        /// \return This builder for chaining.
        HttpRequestBuilder& body(std::string body);

        /// \brief Sets the content type header the request will be built with.
        /// \param content_type The content type.
        /// \return This builder for chaining.
        HttpRequestBuilder& content_type(std::string content_type);

        /// \brief Adds a header for the request.
        /// \param name The header name.
        /// \param value The header value.
        /// \return This builder for chaining.
        HttpRequestBuilder& add_header(std::string name, std::string value);

    private:
        std::optional<HttpMethod> m_method;
        std::string m_path_query_fragment;
        std::string m_body;
        std::string m_content_type;
        std::map<std::string, std::string> headers;

        HttpRequestBuilder() = default;

        friend HttpRequestBuilder HttpRequest::builder();
    };

private:
    const HttpMethod method;
    const std::string path_query_fragment;
    const std::string body;
    const std::string content_type;
    const std::map<std::string, std::string> headers;

    HttpRequest(HttpMethod method,
                std::string path_query_fragment,
                std::string body_data,
                std::string content_type,
                std::map<std::string, std::string> headers);
};

}

#endif //ENJINCPPSDK_HTTPREQUEST_HPP
