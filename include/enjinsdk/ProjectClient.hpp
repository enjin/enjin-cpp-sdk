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

#ifndef ENJINCPPSDK_PROJECTCLIENT_HPP
#define ENJINCPPSDK_PROJECTCLIENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IHttpClient.hpp"
#include "enjinsdk/IClient.hpp"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include "enjinsdk/internal/Timer.hpp"
#include "enjinsdk/models/AccessToken.hpp"
#include "enjinsdk/project/ProjectSchema.hpp"
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

namespace enjin::sdk {

/// \brief Client for using the project schema.
class ENJINSDK_EXPORT ProjectClient : public IClient,
                                      public project::ProjectSchema {
public:
    class ProjectClientBuilder;

    ProjectClient() = delete;

    ProjectClient(const ProjectClient&) = delete;

    ProjectClient(ProjectClient&&) = delete;

    ~ProjectClient() override;

    /// \copydoc IClient::auth(std::string)
    /// \remarks If this client has automatic reauthentication enabled, then this method will halt the reauthentication
    /// timer.
    void auth(std::string token) override;

    /// \brief Authenticates the client using the given access token model.
    /// \param access_token The access token.
    /// \throws std::runtime_error If access_token exclusively returns an empty optional from either its token or
    /// expiration getter.
    /// \remarks If this client has automatic reauthentication enabled, then this method may halt the reauthentication
    /// timer when access_token is null. Otherwise the timer will be restarted.
    void auth(models::AccessToken access_token);

    /// \brief Sends a request to the platform to authenticate this client.
    /// \param uuid The project's UUID.
    /// \param secret The project's secret.
    /// \return The future for this operation.
    /// \throws std::runtime_error If this client is closed at the time this method is called.
    /// \remarks If this client is enabled for automatic reauthentication, then it will cache the UUID and secret and
    /// reauthenticate itself before the access token returned by the platform expires.
    std::future<void> auth_client(std::string uuid, std::string secret);

    void close() override;

    [[nodiscard]] bool is_authenticated() const override;

    /// \brief Determines if this client is enabled for automatic reauthentication.
    /// \return Whether this client is enabled for automatic reauthentication.
    [[nodiscard]] bool is_automatic_reauthentication_enabled() const;

    [[nodiscard]] bool is_closed() const override;

    /// \brief Determines if the reauthentication timer is running.
    /// \return Whether the reauthentication timer is running.
    [[nodiscard]] bool is_reauthentication_running() const;

    /// \brief Creates a builder for this class.
    /// \return The builder.
    [[nodiscard]] static ProjectClientBuilder builder();

    /// \brief Builder class for ProjectClient.
    class ENJINSDK_EXPORT ProjectClientBuilder {
    public:
        /// \brief Default destructor.
        ~ProjectClientBuilder() = default;

        /// \brief Builds the client.
        /// \return The client.
        [[nodiscard]] std::unique_ptr<ProjectClient> build();

        /// \brief Sets the base URI of the built-in HTTP client if a client is not provided.
        /// \param base_uri The base URI.
        /// \return This builder for chaining.
        ProjectClientBuilder& base_uri(std::string base_uri);

        /// \brief Enables the client to automatically reauthenticate itself when authenticated through its
        /// auth_client() method.
        /// \return This builder for chaining.
        ProjectClientBuilder& enable_automatic_reauthentication();

        /// \brief Sets the underlying HTTP client implementation to be moved to the client.
        /// \param http_client The client implementation.
        /// \return This builder for chaining.
        ProjectClientBuilder& http_client(std::unique_ptr<http::IHttpClient> http_client);

        /// \brief Sets the HTTP log level to set the HTTP client to.
        /// \param http_log_level The HTTP log level.
        /// \return This builder for chaining.
        ProjectClientBuilder& http_log_level(http::HttpLogLevel http_log_level);

        /// \brief Sets the logger provider to be used by the client.
        /// \param logger_provider The logger provider.
        /// \return This builder for chaining.
        ProjectClientBuilder& logger_provider(std::shared_ptr<utils::LoggerProvider> logger_provider);

        /// \brief Sets the handler to be used by the client after the reauthentication timer is stopped.
        /// \param handler The handler.
        /// \return This builder for chaining.
        ProjectClientBuilder& reauthentication_stopped_handler(std::function<void()> handler);

    private:
        std::optional<std::function<void()>> m_reauthentication_stopped_handler;
        std::optional<std::string> m_base_uri;
        std::optional<bool> m_automatic_reauthentication;
        std::unique_ptr<http::IHttpClient> m_http_client;
        std::optional<http::HttpLogLevel> m_http_log_level;
        std::shared_ptr<utils::LoggerProvider> m_logger_provider;

        ProjectClientBuilder() = default;

        friend ProjectClientBuilder ProjectClient::builder();
    };

private:
    const bool automatic_reauthentication_enabled;
    bool reauthentication_running = false;
    std::unique_ptr<utils::Timer> auth_timer;

    // Auth handlers
    const std::optional<std::function<void()>> reauthentication_stopped_handler;

    std::optional<std::string> uuid;
    std::optional<std::string> secret;

    // Mutexes
    mutable std::mutex auth_mutex;

    ProjectClient(TrustedPlatformMiddleware middleware,
                  bool automatic_reauthentication,
                  std::shared_ptr<utils::LoggerProvider> logger_provider,
                  std::optional<std::function<void()>> reauthentication_stopped_handler);

    void auth(std::optional<std::string> token, std::optional<long> expires_in);

    bool restart_authentication_timer(std::optional<long> expires_in);

    std::future<void> send_request_and_auth(std::string uuid, std::string secret);

    void send_request_and_auth();

    /// \brief Amount of time in seconds to preempt the expiration period of an access token.
    static constexpr short PREEMPT_AUTH_EXPIRATION_TIME = 60;
};

}

#endif //ENJINCPPSDK_PROJECTCLIENT_HPP
