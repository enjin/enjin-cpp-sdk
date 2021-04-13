#ifndef ENJINCPPSDK_PLAYERGETPLAYER_HPP
#define ENJINCPPSDK_PLAYERGETPLAYER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/PlayerFragmentArguments.hpp"

namespace enjin::sdk::player {

/// \brief Request for getting information about the player.
class ENJINSDK_EXPORT GetPlayer : public graphql::AbstractGraphqlRequest,
                                  public shared::PlayerFragmentArguments<GetPlayer> {
public:
    /// \brief Default constructor.
    GetPlayer();

    ~GetPlayer() override = default;

    [[nodiscard]] std::string serialize() const override;

    bool operator==(const GetPlayer& rhs) const;

    bool operator!=(const GetPlayer& rhs) const;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT player::GetPlayer& PlayerFragmentArguments<player::GetPlayer>::set_with_linking_info();

template ENJINSDK_EXPORT player::GetPlayer& PlayerFragmentArguments<player::GetPlayer>::set_qr_size(int size);

template ENJINSDK_EXPORT player::GetPlayer& PlayerFragmentArguments<player::GetPlayer>::set_with_wallet();

}

#endif //ENJINCPPSDK_PLAYERGETPLAYER_HPP
