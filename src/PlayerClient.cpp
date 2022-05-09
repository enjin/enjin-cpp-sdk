/* Copyright 2021 Enjin Pte. Ltd.
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

#include "HttpClient.hpp"

#endif

namespace enjin::sdk {

PlayerClient::PlayerClient(std::unique_ptr<http::IHttpClient> http_client,
                           std::shared_ptr<utils::LoggerProvider> logger_provider)
        : PlayerSchema(std::move(http_client), std::move(logger_provider)) {
}

PlayerClient::~PlayerClient() {
    PlayerClient::close();
}

void PlayerClient::auth(std::string token) {
    middleware->set_auth_token(token);
}

void PlayerClient::close() {
    middleware->close();
}

bool PlayerClient::is_authenticated() const {
    return middleware->is_authenticated();
}

bool PlayerClient::is_closed() const {
    return middleware->is_closed();
}

PlayerClient::PlayerClientBuilder PlayerClient::builder() {
    return {};
}

std::unique_ptr<PlayerClient> PlayerClient::PlayerClientBuilder::build() {
    if (m_http_client == nullptr) {
#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
        if (!m_base_uri.has_value()) {
            throw std::runtime_error("No base URI was set for default HTTP client implementation");
        }

        auto client = std::make_unique<http::HttpClient>(m_base_uri.value());
        auto log_level = m_http_log_level.value_or(http::HttpLogLevel::NONE);
        if (log_level != http::HttpLogLevel::NONE && m_logger_provider != nullptr) {
            client->set_logger(log_level, m_logger_provider);
        }

        return std::unique_ptr<PlayerClient>(new PlayerClient(std::move(client),
                                                              m_logger_provider));
#else
        throw std::runtime_error("Attempted building platform client without providing an HTTP client");
#endif
    } else {
        return std::unique_ptr<PlayerClient>(new PlayerClient(std::move(m_http_client),
                                                              m_logger_provider));
    }
}

PlayerClient::PlayerClientBuilder& PlayerClient::PlayerClientBuilder::base_uri(std::string base_uri) {
    m_base_uri = std::move(base_uri);
    return *this;
}

PlayerClient::PlayerClientBuilder&
PlayerClient::PlayerClientBuilder::http_client(std::unique_ptr<http::IHttpClient> http_client) {
    m_http_client = std::move(http_client);
    return *this;
}

PlayerClient::PlayerClientBuilder&
PlayerClient::PlayerClientBuilder::http_log_level(http::HttpLogLevel http_log_level) {
    m_http_log_level = http_log_level;
    return *this;
}

PlayerClient::PlayerClientBuilder&
PlayerClient::PlayerClientBuilder::logger_provider(std::shared_ptr<utils::LoggerProvider> logger_provider) {
    m_logger_provider = std::move(logger_provider);
    return *this;
}

}
