#ifndef ENJINCPPSDK_HTTPREQUEST_HPP
#define ENJINCPPSDK_HTTPREQUEST_HPP

#include "enjinsdk_export.h"
#include <map>
#include <string>

namespace enjin::sdk::http {

class HttpRequest;

/// \brief Builder class for HttpRequest class.
class ENJINSDK_EXPORT HttpRequestBuilder {
public:
    /// \brief Default constructor.
    HttpRequestBuilder() = default;

    /// \brief Default destructor.
    ~HttpRequestBuilder() = default;

    /// \brief Builds the request.
    /// \return The built request.
    HttpRequest build();

    /// \brief Sets the HTTP method the request will be built with.
    /// \param method The HTTP method.
    /// \return This builder for chaining.
    HttpRequestBuilder& method(const std::string& method);

    /// \brief Sets the path query fragment the request will be built with.
    /// \param path_query_fragment The path query fragment.
    /// \return This builder for chaining.
    HttpRequestBuilder& path_query_fragment(const std::string& path_query_fragment);

    /// \brief Sets the body data the request will be built with.
    /// \param body The request body.
    /// \return This builder for chaining.
    HttpRequestBuilder& body(const std::string& body);

    /// \brief Sets the content type header the request will be built with.
    /// \param content_type The content type.
    /// \return This builder for chaining.
    HttpRequestBuilder& content_type(const std::string& content_type);

    /// \brief Adds a header for the request.
    /// \param name The header name.
    /// \param value The header value.
    /// \return This builder for chaining.
    HttpRequestBuilder& add_header(const std::string& name, const std::string& value);

private:
    std::string m_method;
    std::string m_path_query_fragment;
    std::string m_body;
    std::string m_content_type;
    std::map<std::string, std::string> headers;
};

/// \brief Container class for a HTTP request.
class ENJINSDK_EXPORT HttpRequest {
public:
    HttpRequest() = delete;

    /// \brief Default destructor.
    ~HttpRequest() = default;

    /// \brief Returns the HTTP method of this request.
    /// \return The HTTP method.
    [[nodiscard]] std::string get_method() const;

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
    /// \throws Throws std::out_of_range if no value is mapped for the header.
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

private:
    const std::string method;
    const std::string path_query_fragment;
    const std::string body;
    const std::string content_type;
    const std::map<std::string, std::string> headers;

    HttpRequest(std::string method,
                std::string path_query_fragment,
                std::string body_data,
                std::string content_type,
                std::map<std::string, std::string> headers);

    friend HttpRequest HttpRequestBuilder::build();
};

}

#endif //ENJINCPPSDK_HTTPREQUEST_HPP
