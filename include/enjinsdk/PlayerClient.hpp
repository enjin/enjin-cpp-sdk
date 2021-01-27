#ifndef ENJINCPPSDK_PLAYERCLIENT_HPP
#define ENJINCPPSDK_PLAYERCLIENT_HPP

#include "enjinsdk/AbstractHttpClient.hpp"
#include "enjinsdk/IClient.hpp"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include "enjinsdk/player/PlayerSchema.hpp"
#include <optional>
#include <string>

namespace enjin::sdk {

class PlayerClient;

/// \brief Builder class for PlayerClient.
class PlayerClientBuilder {
public:
    /// \brief Default constructor.
    PlayerClientBuilder() = default;

    /// \brief Default destructor.
    ~PlayerClientBuilder() = default;

    /// \brief Builds the client.
    /// \return The clients.
    PlayerClient build();

    /// \brief Sets the base URI of the underlying HTTP client if one is not provided.
    /// \param base_uri The base URI.
    /// \return This builder for chaining.
    PlayerClientBuilder& base_uri(const std::string& base_uri);

    /// \brief Sets the underlying HTTP client implementation for the platform client to use.
    /// \param http_client The client implementation.
    /// \return This builder for chaining.
    PlayerClientBuilder& http_client(http::AbstractHttpClient& http_client);

    /// \brief Sets whether the client will have debugging enabled.
    /// \param debug The debug state.
    /// \return This builder for chaining.
    PlayerClientBuilder& debug(int debug);

private:
    std::optional<std::string> m_base_uri;
    std::optional<http::AbstractHttpClient*> m_http_client;
    std::optional<bool> m_debug;
};

/// \brief Client for using the player schema.
class PlayerClient : public IClient,
                     public player::PlayerSchema {
public:
    ~PlayerClient() override = default;

    void auth(const std::string& token) override;

    bool is_authenticated() override;

    bool is_closed() override;

private:
    explicit PlayerClient(const TrustedPlatformMiddleware& middleware);

    friend PlayerClient PlayerClientBuilder::build();
};

}

#endif //ENJINCPPSDK_PLAYERCLIENT_HPP
