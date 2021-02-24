#ifndef ENJINCPPSDK_PROJECTCLIENT_HPP
#define ENJINCPPSDK_PROJECTCLIENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IHttpClient.hpp"
#include "enjinsdk/IClient.hpp"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include "enjinsdk/project/ProjectSchema.hpp"
#include <optional>
#include <string>

namespace enjin::sdk {

class ProjectClient;

/// \brief Builder class for ProjectClient.
class ENJINSDK_EXPORT ProjectClientBuilder {
public:
    /// \brief Default constructor.
    ProjectClientBuilder() = default;

    /// \brief Default destructor.
    ~ProjectClientBuilder() = default;

    /// \brief Builds the client.
    /// \return The clients.
    ProjectClient build();

    /// \brief Sets the base URI of the underlying HTTP client if one is not provided.
    /// \param base_uri The base URI.
    /// \return This builder for chaining.
    ProjectClientBuilder& base_uri(const std::string& base_uri);

    /// \brief Sets the underlying HTTP client implementation for the platform client to use.
    /// \param http_client The client implementation.
    /// \return This builder for chaining.
    ProjectClientBuilder& http_client(std::unique_ptr<http::IHttpClient> http_client);

    /// \brief Sets whether the client will have debugging enabled.
    /// \param debug The debug state.
    /// \return This builder for chaining.
    ProjectClientBuilder& debug(bool debug);

private:
    std::optional<std::string> m_base_uri;
    std::unique_ptr<http::IHttpClient> m_http_client;
    std::optional<bool> m_debug;
};

/// \brief Client for using the project schema.
class ENJINSDK_EXPORT ProjectClient : public IClient,
                                      public project::ProjectSchema {
public:
    ~ProjectClient() override = default;

    void auth(const std::string& token) override;

    bool is_authenticated() override;

    bool is_closed() override;

private:
    explicit ProjectClient(TrustedPlatformMiddleware middleware);

    friend ProjectClient ProjectClientBuilder::build();
};

}

#endif //ENJINCPPSDK_PROJECTCLIENT_HPP
