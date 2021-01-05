#include "enjinsdk/AbstractHttpClient.hpp"

namespace enjin::sdk::http {

AbstractHttpClient::AbstractHttpClient(const std::string& base_uri) : base_uri(base_uri) {
}

bool AbstractHttpClient::set_base_uri(const std::string& uri) {
    if (base_uri.has_value()) {
        return false;
    }

    base_uri.emplace(uri);
    return true;
}

}
