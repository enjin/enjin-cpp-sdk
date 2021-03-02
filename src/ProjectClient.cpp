#include "enjinsdk/ProjectClient.hpp"

#include <exception>
#include <utility>

#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL

#include "HttpClientImpl.hpp"

#endif

namespace enjin::sdk {

ProjectClient::ProjectClient(TrustedPlatformMiddleware middleware) : ProjectSchema(std::move(middleware)) {
}

void ProjectClient::auth(const std::string& token) {
    middleware.get_handler()->set_auth_token(token);
}

bool ProjectClient::is_authenticated() {
    return middleware.get_handler()->is_authenticated();
}

bool ProjectClient::is_closed() {
    // TODO: Implement function.
    return false;
}

ProjectClient ProjectClientBuilder::build() {
    if (m_http_client == nullptr) {
#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
        m_http_client = std::make_unique<http::HttpClientImpl>(m_base_uri.has_value()
                                                               ? m_base_uri.value()
                                                               : throw std::exception(
                        "No base URI was set for default HTTP client implementation"));
        TrustedPlatformMiddleware middleware(std::move(m_http_client), m_debug.has_value() && m_debug.value());
        return ProjectClient(std::move(middleware));
#else
        throw std::exception("Attempted building platform client without providing an HTTP client");
#endif
    } else {
        TrustedPlatformMiddleware middleware(std::move(m_http_client), m_debug.has_value() && m_debug.value());
        return ProjectClient(std::move(middleware));
    }
}

ProjectClientBuilder& ProjectClientBuilder::base_uri(const std::string& base_uri) {
    m_base_uri = base_uri;
    return *this;
}

ProjectClientBuilder& ProjectClientBuilder::http_client(std::unique_ptr<http::IHttpClient> http_client) {
    m_http_client = std::move(http_client);
    return *this;
}

ProjectClientBuilder& ProjectClientBuilder::debug(bool debug) {
    m_debug = debug;
    return *this;
}

}
