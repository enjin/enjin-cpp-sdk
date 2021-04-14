#ifndef ENJINCPPSDK_HTTPRESPONSE_HPP
#define ENJINCPPSDK_HTTPRESPONSE_HPP

#include "enjinsdk_export.h"
#include <optional>
#include <string>

namespace enjin::sdk::http {

class HttpResponse;

/// \brief Builder class for HttpResponse class.
class ENJINSDK_EXPORT HttpResponseBuilder {
public:
    /// \brief Default constructor.
    HttpResponseBuilder() = default;

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
    HttpResponseBuilder& body(const std::string& body);

    /// \brief Sets the content type header the response will be built with.
    /// \param content_type The content type.
    /// \return This builder for chaining.
    HttpResponseBuilder& content_type(const std::string& content_type);

private:
    std::optional<unsigned short> m_code;
    std::optional<std::string> m_body;
    std::optional<std::string> m_content_type;
};

/// \brief Container class for a HTTP response.
class ENJINSDK_EXPORT HttpResponse {
public:
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

    /// \brief Returns the optional with the content type header.
    /// \return The content type optional.
    [[nodiscard]] const std::optional<std::string>& get_content_type() const;

    bool operator==(const HttpResponse& rhs) const;

    bool operator!=(const HttpResponse& rhs) const;

private:
    std::optional<unsigned short> code;
    std::optional<std::string> body;
    std::optional<std::string> content_type;

    HttpResponse(std::optional<unsigned short> code,
                 std::optional<std::string>,
                 std::optional<std::string> content_type);

    friend HttpResponse HttpResponseBuilder::build();
};

}

#endif //ENJINCPPSDK_HTTPRESPONSE_HPP
