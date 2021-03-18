#ifndef ENJINCPPSDK_PROJECTGETPLAYER_HPP
#define ENJINCPPSDK_PROJECTGETPLAYER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/PlayerFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for getting a player on the platform.
class ENJINSDK_EXPORT GetPlayer : public graphql::AbstractGraphqlRequest,
                                  public shared::PlayerFragmentArguments<GetPlayer> {
public:
    /// \brief Default constructor.
    GetPlayer();

    ~GetPlayer() override = default;

    std::string serialize() override;

    /// \brief Sets the player ID.
    /// \param id The ID.
    /// \return This request for chaining.
    GetPlayer& set_id(const std::string& id);

    bool operator==(const GetPlayer& rhs) const;

    bool operator!=(const GetPlayer& rhs) const;

private:
    std::optional<std::string> id;
};

}

#endif //ENJINCPPSDK_PROJECTGETPLAYER_HPP
