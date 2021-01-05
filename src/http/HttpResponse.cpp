#include "enjinsdk/HttpResponse.hpp"
#include "rapidjson/document.h"

namespace enjin::sdk::http {

HttpResponse::HttpResponse(uint16_t code, const std::string& body) : code(code), body(body) {
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

}
