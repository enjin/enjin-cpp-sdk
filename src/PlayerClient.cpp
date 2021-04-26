/* Copyright 2021 Enjin Pte Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

PlayerClient::PlayerClient(TrustedPlatformMiddleware middleware, std::shared_ptr<utils::LoggerProvider> logger_provider)
        : PlayerSchema(std::move(middleware), std::move(logger_provider)) {
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

        TrustedPlatformMiddleware middleware(std::make_unique<http::HttpClientImpl>(m_base_uri.value(),
                                                                                    m_logger_provider));
        return std::unique_ptr<PlayerClient>(new PlayerClient(std::move(middleware), m_logger_provider));
#else
        throw std::runtime_error("Attempted building platform client without providing an HTTP client");
#endif
    } else {
        TrustedPlatformMiddleware middleware(std::move(m_http_client));
        return std::unique_ptr<PlayerClient>(new PlayerClient(std::move(middleware), m_logger_provider));
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

PlayerClientBuilder& PlayerClientBuilder::logger_provider(std::shared_ptr<utils::LoggerProvider> logger_provider) {
    m_logger_provider = std::move(logger_provider);
    return *this;
}

}
