#include "enjinsdk/ProjectClient.hpp"

#include <stdexcept>
#include <utility>

#ifndef ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
#define ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL

#include "HttpClientImpl.hpp"

#endif

namespace enjin::sdk {

ProjectClient::ProjectClient(TrustedPlatformMiddleware middleware, std::shared_ptr<utils::Logger> logger)
        : ProjectSchema(std::move(middleware), std::move(logger)) {
}

ProjectClient::~ProjectClient() {
    close();
}

void ProjectClient::auth(const std::string& token) {
    middleware.get_handler()->set_auth_token(token);
}

void ProjectClient::close() {
    middleware.get_client()->stop();
}

bool ProjectClient::is_authenticated() {
    return middleware.get_handler()->is_authenticated();
}

bool ProjectClient::is_closed() {
    return !middleware.get_client()->is_open();
}

std::unique_ptr<ProjectClient> ProjectClientBuilder::build() {
    if (m_http_client == nullptr) {
#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
        m_http_client = std::make_unique<http::HttpClientImpl>(m_base_uri.has_value()
                                                               ? m_base_uri.value()
                                                               : throw std::runtime_error(
                        "No base URI was set for default HTTP client implementation"),
                                                               m_logger);
        TrustedPlatformMiddleware middleware(std::move(m_http_client), m_debug.has_value() && m_debug.value());
        return std::unique_ptr<ProjectClient>(new ProjectClient(std::move(middleware), m_logger));
#else
        throw std::runtime_error("Attempted building platform client without providing an HTTP client");
#endif
    } else {
        TrustedPlatformMiddleware middleware(std::move(m_http_client), m_debug.has_value() && m_debug.value());
        return std::unique_ptr<ProjectClient>(new ProjectClient(std::move(middleware), m_logger));
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

ProjectClientBuilder& ProjectClientBuilder::logger(std::shared_ptr<utils::Logger> logger) {
    m_logger = std::move(logger);
    return *this;
}

}
