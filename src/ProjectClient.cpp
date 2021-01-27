#include "enjinsdk/ProjectClient.hpp"

#include "HttpClientImpl.hpp" // TODO: Don't include if cpprestsdk is not installed.

namespace enjin::sdk {

ProjectClient::ProjectClient(const TrustedPlatformMiddleware& middleware) : ProjectSchema(middleware) {
}

void ProjectClient::auth(const std::string& token) {

}

bool ProjectClient::is_authenticated() {
    return false;
}

bool ProjectClient::is_closed() {
    return false;
}

ProjectClient ProjectClientBuilder::build() {
    /* TODO: Use compile-time macros to only allow HttpClientImpl if cpprestsdk is installed and require a client be
     *       passed in if not.
     */
    http::AbstractHttpClient* client = m_http_client.has_value()
                                       ? m_http_client.value()
                                       : new http::HttpClientImpl(m_base_uri.has_value()
                                                                  ? m_base_uri.value()
                                                                  : throw std::exception("No base URI was set for default HTTP client implementation"));

    TrustedPlatformMiddleware middleware(*client, m_debug.has_value() && m_debug.value());
    return ProjectClient(middleware);
}

ProjectClientBuilder& ProjectClientBuilder::base_uri(const std::string& base_uri) {
    m_base_uri = base_uri;
    return *this;
}

ProjectClientBuilder& ProjectClientBuilder::http_client(http::AbstractHttpClient& client) {
    m_http_client = &client;
    return *this;
}

ProjectClientBuilder& ProjectClientBuilder::debug(bool debug) {
    m_debug = debug;
    return *this;
}

}
