#include "enjinsdk/AbstractHttpClient.hpp"

#include <utility>

namespace enjin::sdk::http {

AbstractHttpClient::AbstractHttpClient(std::string base_uri) : base_uri(std::move(base_uri)) {
}

std::string AbstractHttpClient::get_base_uri() {
    return base_uri;
}

}
