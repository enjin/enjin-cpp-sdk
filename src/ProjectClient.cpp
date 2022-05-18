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

#include "enjinsdk/ProjectClient.hpp"

#include <chrono>
#include <stdexcept>
#include <utility>

#ifndef ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
#define ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL

#include "HttpClient.hpp"

#endif

namespace enjin::sdk {

ProjectClient::ProjectClient(std::unique_ptr<http::IHttpClient> http_client,
                             bool automatic_reauthentication,
                             std::shared_ptr<utils::LoggerProvider> logger_provider,
                             std::optional<std::function<void()>> reauthentication_stopped_handler)
        : ProjectSchema(std::move(http_client), std::move(logger_provider)),
          automatic_reauthentication_enabled(automatic_reauthentication),
          reauthentication_stopped_handler(std::move(reauthentication_stopped_handler)) {
    if (automatic_reauthentication) {
        auth_timer = std::make_unique<utils::Timer>();
    }
}

ProjectClient::~ProjectClient() {
    ProjectClient::close();
}

void ProjectClient::auth(std::string token) {
    auth(token, std::nullopt);
}

void ProjectClient::auth(models::AccessToken access_token) {
    const auto& token = access_token.get_token();
    const auto& expires_in = access_token.get_expires_in();
    if (token.has_value() ^ expires_in.has_value()) {
        throw std::runtime_error("Access token has partial data.");
    }

    auth(token, expires_in);
}

std::future<void> ProjectClient::auth_client(std::string uuid, std::string secret) {
    if (is_closed()) {
        throw std::runtime_error("Cannot authenticate after client was closed.");
    }

    if (is_automatic_reauthentication_enabled()) {
        std::unique_lock<std::mutex> lock(auth_mutex);
        ProjectClient::uuid = uuid;
        ProjectClient::secret = secret;
        lock.unlock();
    }

    return send_request_and_auth(uuid, secret);
}

void ProjectClient::close() {
    std::unique_lock<std::mutex> lock(auth_mutex);
    if (auth_timer != nullptr) {
        auth_timer->cancel();
        reauthentication_running = false;
    }
    lock.unlock();

    middleware->close();
}

bool ProjectClient::is_authenticated() const {
    return middleware->is_authenticated();
}

bool ProjectClient::is_automatic_reauthentication_enabled() const {
    return automatic_reauthentication_enabled;
}

bool ProjectClient::is_closed() const {
    return middleware->is_closed();
}

bool ProjectClient::is_reauthentication_running() const {
    std::lock_guard<std::mutex> guard(auth_mutex);
    return reauthentication_running;
}

ProjectClient::ProjectClientBuilder ProjectClient::builder() {
    return {};
}

void ProjectClient::auth(std::optional<std::string> token, std::optional<long> expires_in) {
    bool timer_restarted = false;
    std::unique_lock<std::mutex> lock(auth_mutex);
    if (is_automatic_reauthentication_enabled() && uuid.has_value() && secret.has_value()) {
        timer_restarted = restart_authentication_timer(expires_in);
    }
    lock.unlock();

    middleware->set_auth_token(token.value_or(""));

    if (reauthentication_stopped_handler.has_value() && auth_timer != nullptr && !timer_restarted) {
        reauthentication_stopped_handler.value()();
    }
}

bool ProjectClient::restart_authentication_timer(std::optional<long> expires_in) {
    auth_timer->cancel();
    reauthentication_running = false;

    if (!expires_in.has_value() || expires_in.value() <= 0) {
        return false;
    }

    auto duration = expires_in.value();
    if (duration - PREEMPT_AUTH_EXPIRATION_TIME > 0) {
        duration -= PREEMPT_AUTH_EXPIRATION_TIME;
    }

    auth_timer->schedule([this]() {
        send_request_and_auth();
    }, std::chrono::milliseconds(duration * 1000));
    reauthentication_running = true;

    return true;
}

std::future<void> ProjectClient::send_request_and_auth(std::string uuid, std::string secret) {
    return std::async([this, uuid = std::move(uuid), secret = std::move(secret)]() {
        auto req = project::AuthProject()
                .set_uuid(uuid)
                .set_secret(secret);
        try {
            auto res = auth_project(req).get();
            if (res.is_successful()) {
                auth(res.get_result().value());
            } else {
                auth(std::nullopt, std::nullopt);
            }
        } catch (const std::exception& e) {
            if (logger_provider != nullptr) {
                logger_provider->log(utils::LogLevel::ERR, "Automatic AuthProject request failed.", e);
            }

            throw e;
        }
    });
}

void ProjectClient::send_request_and_auth() {
    std::unique_lock<std::mutex> lock(auth_mutex);
    if (!uuid.has_value() || !secret.has_value()) {
        throw std::runtime_error("UUID or secret are not set while attempting reauthentication.");
    }

    std::string uuid = ProjectClient::uuid.value();
    std::string secret = ProjectClient::secret.value();
    lock.unlock();

    send_request_and_auth(uuid, secret);
}

std::unique_ptr<ProjectClient> ProjectClient::ProjectClientBuilder::build() {
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

        return std::unique_ptr<ProjectClient>(new ProjectClient(std::move(client),
                                                                m_automatic_reauthentication.value_or(false),
                                                                m_logger_provider,
                                                                std::move(m_reauthentication_stopped_handler)));
#else
        throw std::runtime_error("Attempted building platform client without providing an HTTP client");
#endif
    } else {
        return std::unique_ptr<ProjectClient>(new ProjectClient(std::move(m_http_client),
                                                                m_automatic_reauthentication.value_or(false),
                                                                m_logger_provider,
                                                                std::move(m_reauthentication_stopped_handler)));
    }
}

ProjectClient::ProjectClientBuilder& ProjectClient::ProjectClientBuilder::base_uri(std::string base_uri) {
    m_base_uri = std::move(base_uri);
    return *this;
}

ProjectClient::ProjectClientBuilder& ProjectClient::ProjectClientBuilder::enable_automatic_reauthentication() {
    m_automatic_reauthentication = true;
    return *this;
}

ProjectClient::ProjectClientBuilder&
ProjectClient::ProjectClientBuilder::http_client(std::unique_ptr<http::IHttpClient> http_client) {
    m_http_client = std::move(http_client);
    return *this;
}

ProjectClient::ProjectClientBuilder&
ProjectClient::ProjectClientBuilder::http_log_level(http::HttpLogLevel http_log_level) {
    m_http_log_level = http_log_level;
    return *this;
}

ProjectClient::ProjectClientBuilder&
ProjectClient::ProjectClientBuilder::logger_provider(std::shared_ptr<utils::LoggerProvider> logger_provider) {
    m_logger_provider = std::move(logger_provider);
    return *this;
}

ProjectClient::ProjectClientBuilder&
ProjectClient::ProjectClientBuilder::reauthentication_stopped_handler(std::function<void()> handler) {
    m_reauthentication_stopped_handler = std::move(handler);
    return *this;
}

}
