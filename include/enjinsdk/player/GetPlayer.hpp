#ifndef ENJINCPPSDK_GETPLAYER_HPP
#define ENJINCPPSDK_GETPLAYER_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/PlayerFragmentArgumentsTemplate.hpp"

namespace enjin::sdk::player {

/// \brief Request for getting information about the player.
class GetPlayer : public graphql::AbstractGraphqlRequest,
                  public shared::PlayerFragmentArgumentsTemplate<GetPlayer> {
public:
    /// \brief Default constructor.
    GetPlayer();

    ~GetPlayer() override = default;

    std::string serialize() override;

    bool operator==(const GetPlayer& rhs) const;

    bool operator!=(const GetPlayer& rhs) const;
};

}

#endif //ENJINCPPSDK_GETPLAYER_HPP
