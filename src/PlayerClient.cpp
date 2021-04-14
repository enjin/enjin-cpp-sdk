#include "enjinsdk/PlayerClient.hpp"

#include <stdexcept>
#include <utility>

#ifndef ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
#define ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL

#include "HttpClientImpl.hpp"

#endif

namespace enjin::sdk {

PlayerClient::PlayerClient(TrustedPlatformMiddleware middleware, std::shared_ptr<utils::Logger> logger)
        : PlayerSchema(std::move(middleware), std::move(logger)) {
}

PlayerClient::~PlayerClient() {
    close();
}

void PlayerClient::auth(const std::string& token) {
    middleware.get_handler()->set_auth_token(token);
}

void PlayerClient::close() {
    middleware.get_client()->stop();
}

bool PlayerClient::is_authenticated() const {
    return middleware.get_handler()->is_authenticated();
}

bool PlayerClient::is_closed() const {
    return !middleware.get_client()->is_open();
}

std::unique_ptr<PlayerClient> PlayerClientBuilder::build() {
    if (m_http_client == nullptr) {
#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
        if (!m_base_uri.has_value()) {
            throw std::runtime_error("No base URI was set for default HTTP client implementation");
        }

        TrustedPlatformMiddleware middleware(std::make_unique<http::HttpClientImpl>(m_base_uri.value(), m_logger));
        return std::unique_ptr<PlayerClient>(new PlayerClient(std::move(middleware), m_logger));
#else
        throw std::runtime_error("Attempted building platform client without providing an HTTP client");
#endif
    } else {
        TrustedPlatformMiddleware middleware(std::move(m_http_client));
        return std::unique_ptr<PlayerClient>(new PlayerClient(std::move(middleware), m_logger));
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

PlayerClientBuilder& PlayerClientBuilder::logger(std::shared_ptr<utils::Logger> logger) {
    m_logger = std::move(logger);
    return *this;
}

}
