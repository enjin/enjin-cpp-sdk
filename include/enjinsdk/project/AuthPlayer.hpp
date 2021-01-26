#ifndef ENJINCPPSDK_PROJECTAUTHPLAYER_HPP
#define ENJINCPPSDK_PROJECTAUTHPLAYER_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request to obtain an access token for a player.
class AuthPlayer : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    AuthPlayer();

    ~AuthPlayer() override = default;

    std::string serialize() override;

    /// \brief Sets the player ID.
    /// \param id The ID.
    /// \return This request for chaining.
    AuthPlayer& set_id(const std::string& id);

    bool operator==(const AuthPlayer& rhs) const;

    bool operator!=(const AuthPlayer& rhs) const;

private:
    std::optional<std::string> id;
};

}

#endif //ENJINCPPSDK_PROJECTAUTHPLAYER_HPP
