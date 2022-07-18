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

#ifndef ENJINCPPSDK_HTTPRESPONSE_HPP
#define ENJINCPPSDK_HTTPRESPONSE_HPP

#include "enjinsdk_export.h"
#include <map>
#include <optional>
#include <string>

namespace enjin::sdk::http {

/// \brief Container class for a HTTP response.
class ENJINSDK_EXPORT HttpResponse {
public:
    class HttpResponseBuilder;

    /// \brief Default constructor.
    HttpResponse() = default;

    /// \brief Default destructor.
    ~HttpResponse() = default;

    /// \brief True if the status code is in the range [200-300).
    /// \return True if 2xx, false otherwise.
    [[nodiscard]] bool is_success() const;

    /// \brief Determines if the response body is empty.
    /// \return Whether the response body is empty.
    [[nodiscard]] bool is_empty() const;

    /// \brief Returns the optional with the status code.
    /// \return The status code optional.
    [[nodiscard]] const std::optional<unsigned short>& get_code() const;

    /// \brief Returns the optional with the response body.
    /// \return The response body optional.
    [[nodiscard]] const std::optional<std::string>& get_body() const;

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

    bool operator==(const HttpResponse& rhs) const;

    bool operator!=(const HttpResponse& rhs) const;

    /// \brief Creates a builder for this class.
    /// \return The builder.
    [[nodiscard]] static HttpResponseBuilder builder();

    /// \brief Builder class for HttpResponse.
    class ENJINSDK_EXPORT HttpResponseBuilder {
    public:
        /// \brief Default destructor.
        ~HttpResponseBuilder() = default;

        /// \brief Builds the response.
        /// \return The built response.
        [[nodiscard]] HttpResponse build();

        /// \brief Sets the status code the response will be built with.
        /// \param code The status code.
        /// \return This builder for chaining.
        HttpResponseBuilder& code(unsigned short code);

        /// \brief Sets the body data the response will be built with.
        /// \param body The response body.
        /// \return This builder for chaining.
        HttpResponseBuilder& body(std::string body);

        /// \brief Adds a header for the response to be built with.
        /// \param name The header name.
        /// \param value The header value.
        /// \return This builder for chaining.
        HttpResponseBuilder& add_header(std::string name, std::string value);

    private:
        std::optional<unsigned short> m_code;
        std::optional<std::string> m_body;
        std::map<std::string, std::string> headers;

        HttpResponseBuilder() = default;

        friend HttpResponseBuilder HttpResponse::builder();
    };

private:
    std::optional<unsigned short> code;
    std::optional<std::string> body;
    std::map<std::string, std::string> headers;

    HttpResponse(std::optional<unsigned short> code,
                 std::optional<std::string>,
                 std::map<std::string, std::string> headers);
};

}

#endif //ENJINCPPSDK_HTTPRESPONSE_HPP
