#include "enjinsdk/PlayerClient.hpp"

#include "HttpClientImpl.hpp" // TODO: Don't include if cpprestsdk is not installed.

namespace enjin::sdk {

PlayerClient::PlayerClient(const TrustedPlatformMiddleware& middleware) : PlayerSchema(middleware) {
}

void PlayerClient::auth(const std::string& token) {

}

bool PlayerClient::is_authenticated() {
    return false;
}

bool PlayerClient::is_closed() {
    return false;
}

PlayerClient PlayerClientBuilder::build() {
    /* TODO: Use compile-time macros to only allow HttpClientImpl if cpprestsdk is installed and require a client be
     *       passed in if not.
     */
    http::AbstractHttpClient* client = m_http_client.has_value()
                                       ? m_http_client.value()
                                       : new http::HttpClientImpl(m_base_uri.has_value()
                                                                  ? m_base_uri.value()
                                                                  : throw std::exception("No base URI was set for default HTTP client implementation"));

    TrustedPlatformMiddleware middleware(*client, m_debug.has_value() && m_debug.value());
    return PlayerClient(middleware);
}

PlayerClientBuilder& PlayerClientBuilder::base_uri(const std::string& base_uri) {
    m_base_uri = base_uri;
    return *this;
}

PlayerClientBuilder& PlayerClientBuilder::http_client(http::AbstractHttpClient& http_client) {
    m_http_client = &http_client;
    return *this;
}

PlayerClientBuilder& PlayerClientBuilder::debug(int debug) {
    m_debug = debug;
    return *this;
}

}
