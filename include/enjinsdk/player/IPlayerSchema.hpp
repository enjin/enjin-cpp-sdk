#ifndef ENJINCPPSDK_IPLAYERSCHEMA_HPP
#define ENJINCPPSDK_IPLAYERSCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/player/GetPlayer.hpp"
#include "enjinsdk/player/GetWallet.hpp"
#include "enjinsdk/player/UnlinkWallet.hpp"
#include "enjinsdk/models/Player.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include <future>

namespace enjin::sdk::player {

/// \brief Interface for player schema implementation.
class ENJINSDK_EXPORT IPlayerSchema {
public:
    /// \brief Default destructor.
    virtual ~IPlayerSchema() = default;

    /// \brief Sends GetPlayer request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Player>> get_player_async(GetPlayer& request) = 0;

    /// \brief Sends GetPlayer request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Player> get_player_sync(GetPlayer& request) = 0;

    /// \brief Sends GetWallet request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet_async(GetWallet& request) = 0;

    /// \brief Sends GetWallet request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Wallet> get_wallet_sync(GetWallet& request) = 0;

    /// \brief Sends UnlinkWallet request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> unlink_wallet_async(UnlinkWallet& request) = 0;

    /// \brief Sends UnlinkWallet request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<bool> unlink_wallet_sync(UnlinkWallet& request) = 0;
};

}

#endif //ENJINCPPSDK_IPLAYERSCHEMA_HPP
