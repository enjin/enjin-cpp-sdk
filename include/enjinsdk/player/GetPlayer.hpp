#ifndef ENJINCPPSDK_PLAYERGETPLAYER_HPP
#define ENJINCPPSDK_PLAYERGETPLAYER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/PlayerFragmentArguments.hpp"

namespace enjin::sdk::player {

/// \brief Request for getting information about the player.
class ENJINSDK_EXPORT GetPlayer : public graphql::AbstractGraphqlRequest,
                                  public shared::PlayerFragmentArguments<GetPlayer> {
public:
    /// \brief Default constructor.
    GetPlayer();

    ~GetPlayer() override = default;

    std::string serialize() override;

    bool operator==(const GetPlayer& rhs) const;

    bool operator!=(const GetPlayer& rhs) const;
};

}

#endif //ENJINCPPSDK_PLAYERGETPLAYER_HPP
