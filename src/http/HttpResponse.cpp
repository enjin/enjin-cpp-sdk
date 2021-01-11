#include "enjinsdk/HttpResponse.hpp"

#include <utility>
#include "rapidjson/document.h"

namespace enjin::sdk::http {

HttpResponse HttpResponseBuilder::build() {
    return HttpResponse(m_code, m_body, m_content_type);
}

HttpResponseBuilder& HttpResponseBuilder::code(uint16_t code) {
    m_code = std::optional<uint16_t>(code);
    return *this;
}

HttpResponseBuilder& HttpResponseBuilder::body(const std::string& body) {
    m_body = std::optional<std::string>(body);
    return *this;
}

HttpResponseBuilder& HttpResponseBuilder::content_type(const std::string& content_type) {
    m_content_type = std::optional<std::string>(content_type);
    return *this;
}

HttpResponse::HttpResponse(std::optional<uint16_t> code,
                           std::optional<std::string> body,
                           std::optional<std::string> content_type) :
        code(code),
        body(std::move(body)),
        content_type(std::move(content_type)) {
}

bool HttpResponse::is_success() {
    return code.has_value() && code.value() >= 200 && code.value() < 300;
}

bool HttpResponse::is_empty() {
    if (!body.has_value()) {
        return true;
    }

    rapidjson::Document document;
    document.Parse(body.value().c_str());

    return body.value().empty() || (document.IsObject() && document.ObjectEmpty());
}

std::optional<uint16_t> HttpResponse::get_code() {
    return code;
}

std::optional<std::string> HttpResponse::get_body() {
    return body;
}

std::optional<std::string> HttpResponse::get_content_type() {
    return content_type;
}

bool HttpResponse::operator==(const HttpResponse& rhs) const {
    bool eq_code = false;
    bool eq_body = false;
    bool eq_content_type = false;

    if (code.has_value() && rhs.code.has_value()) {
        eq_code = code.value() == rhs.code.value();
    } else if (!code.has_value() && !rhs.code.has_value()) {
        eq_code = true;
    }

    if (body.has_value() && rhs.body.has_value()) {
        eq_body = body.value() == rhs.body.value();
    } else if (!body.has_value() && !rhs.body.has_value()) {
        eq_body = true;
    }

    if (content_type.has_value() && rhs.content_type.has_value()) {
        eq_content_type = content_type.value() == rhs.content_type.value();
    } else if (!content_type.has_value() && !rhs.content_type.has_value()) {
        eq_content_type = true;
    }

    return eq_code && eq_body && eq_content_type;
}

bool HttpResponse::operator!=(const HttpResponse& rhs) const {
    return !(rhs == *this);
}

}
