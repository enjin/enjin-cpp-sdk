#ifndef ENJINCPPSDK_PLAYERSCHEMA_HPP
#define ENJINCPPSDK_PLAYERSCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/player/IPlayerSchema.hpp"
#include "enjinsdk/shared/SharedSchema.hpp"

namespace enjin::sdk::player {

/// \brief Class for sending requests in the player schema.
class ENJINSDK_EXPORT PlayerSchema : public IPlayerSchema,
                                     public shared::SharedSchema {
public:
    ~PlayerSchema() override = default;

    std::future<graphql::GraphqlResponse<models::Player>> get_player_async(GetPlayer& request) override;

    graphql::GraphqlResponse<models::Player> get_player_sync(GetPlayer& request) override;

    std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet_async(GetWallet& request) override;

    graphql::GraphqlResponse<models::Wallet> get_wallet_sync(GetWallet& request) override;

    std::future<graphql::GraphqlResponse<bool>> unlink_wallet_async(UnlinkWallet& request) override;

    graphql::GraphqlResponse<bool> unlink_wallet_sync(UnlinkWallet& request) override;

protected:
    /// \brief Constructs the schema with the middleware.
    /// \param middleware The middleware.
    explicit PlayerSchema(TrustedPlatformMiddleware middleware);
};

}

#endif //ENJINCPPSDK_PLAYERSCHEMA_HPP
