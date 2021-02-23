#include "enjinsdk/PlayerClient.hpp"

#include "HttpClientImpl.hpp" // TODO: Don't include if cpprestsdk is not installed.
#include <utility>

namespace enjin::sdk {

PlayerClient::PlayerClient(TrustedPlatformMiddleware middleware) : PlayerSchema(std::move(middleware)) {
}

void PlayerClient::auth(const std::string& token) {
    // TODO: Implement function.
}

bool PlayerClient::is_authenticated() {
    // TODO: Implement function.
    return false;
}

bool PlayerClient::is_closed() {
    // TODO: Implement function.
    return false;
}

PlayerClient PlayerClientBuilder::build() {
    /* TODO: Use compile-time macros to only allow HttpClientImpl if cpprestsdk is installed and require a client be
     *       passed in if not.
     */
    if (m_http_client == nullptr) {
        m_http_client = std::make_unique<http::HttpClientImpl>(m_base_uri.has_value()
                                                               ? m_base_uri.value()
                                                               : throw std::exception(
                        "No base URI was set for default HTTP client implementation"));
        TrustedPlatformMiddleware middleware(std::move(m_http_client), m_debug.has_value() && m_debug.value());
        return PlayerClient(std::move(middleware));
    } else {
        TrustedPlatformMiddleware middleware(std::move(m_http_client), m_debug.has_value() && m_debug.value());
        return PlayerClient(std::move(middleware));
    }
}

PlayerClientBuilder& PlayerClientBuilder::base_uri(const std::string& base_uri) {
    m_base_uri = base_uri;
    return *this;
}

PlayerClientBuilder& PlayerClientBuilder::http_client(std::unique_ptr<http::IHttpClient> http_client) {
    m_http_client = std::move(http_client);
    return *this;
}

PlayerClientBuilder& PlayerClientBuilder::debug(int debug) {
    m_debug = debug;
    return *this;
}

}
