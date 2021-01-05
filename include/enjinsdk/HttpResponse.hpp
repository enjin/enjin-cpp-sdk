#ifndef ENJINCPPSDK_HTTPRESPONSE_HPP
#define ENJINCPPSDK_HTTPRESPONSE_HPP

#include <optional>
#include <string>

namespace enjin::sdk::http {

class HttpResponse {
public:
    HttpResponse() = default;

    HttpResponse(uint16_t code, const std::string& body);

    ~HttpResponse() = default;

    bool is_success();

    bool is_empty();

    std::optional<uint16_t> get_code();

    std::optional<std::string> get_body();

private:
    std::optional<uint16_t> code;
    std::optional<std::string> body;
};

}

#endif //ENJINCPPSDK_HTTPRESPONSE_HPP
