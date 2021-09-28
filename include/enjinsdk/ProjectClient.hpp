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
#include "enjinsdk/project/ProjectSchema.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk {

/// \brief Client for using the project schema.
class ENJINSDK_EXPORT ProjectClient : public IClient,
                                      public project::ProjectSchema {
public:
    class ProjectClientBuilder;

    ProjectClient() = delete;

    ~ProjectClient() override;

    void auth(const std::string& token) override;

    void close() override;

    [[nodiscard]] bool is_authenticated() const override;

    [[nodiscard]] bool is_closed() const override;

    /// \brief Creates a builder for this class.
    /// \return The builder.
    [[nodiscard]] static ProjectClientBuilder builder();

    /// \brief Builder class for ProjectClient.
    class ENJINSDK_EXPORT ProjectClientBuilder {
    public:
        /// \brief Default destructor.
        ~ProjectClientBuilder() = default;

        /// \brief Builds the client and provides the unique pointer for it.
        /// \return The client.
        [[nodiscard]] std::unique_ptr<ProjectClient> build();

        /// \brief Sets the base URI of the underlying HTTP client if one is not provided.
        /// \param base_uri The base URI.
        /// \return This builder for chaining.
        ProjectClientBuilder& base_uri(const std::string& base_uri);

        /// \brief Sets the underlying HTTP client implementation for the platform client to use.
        /// \param http_client The client implementation.
        /// \return This builder for chaining.
        ProjectClientBuilder& http_client(std::unique_ptr<http::IHttpClient> http_client);

        /// \brief Sets the logger provider to be used by the client.
        /// \param logger_provider The logger provider.
        /// \return This builder for chaining.
        ProjectClientBuilder& logger_provider(std::shared_ptr<utils::LoggerProvider> logger_provider);

    private:
        std::optional<std::string> m_base_uri;
        std::unique_ptr<http::IHttpClient> m_http_client;
        std::shared_ptr<utils::LoggerProvider> m_logger_provider;

        ProjectClientBuilder() = default;

        friend ProjectClientBuilder ProjectClient::builder();
    };

private:
    ProjectClient(TrustedPlatformMiddleware middleware, std::shared_ptr<utils::LoggerProvider> logger_provider);
};

}

#endif //ENJINCPPSDK_PROJECTCLIENT_HPP
