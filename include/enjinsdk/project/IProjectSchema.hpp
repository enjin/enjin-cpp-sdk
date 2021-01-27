#ifndef ENJINCPPSDK_IPROJECTSCHEMA_HPP
#define ENJINCPPSDK_IPROJECTSCHEMA_HPP

#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/models/AccessToken.hpp"
#include "enjinsdk/models/Player.hpp"
#include "enjinsdk/models/Request.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include "enjinsdk/project/AuthPlayer.hpp"
#include "enjinsdk/project/AuthProject.hpp"
#include "enjinsdk/project/CreatePlayer.hpp"
#include "enjinsdk/project/CreateToken.hpp"
#include "enjinsdk/project/DecreaseMaxMeltFee.hpp"
#include "enjinsdk/project/DecreaseMaxTransferFee.hpp"
#include "enjinsdk/project/DeletePlayer.hpp"
#include "enjinsdk/project/GetPlayer.hpp"
#include "enjinsdk/project/GetPlayers.hpp"
#include "enjinsdk/project/GetWallet.hpp"
#include "enjinsdk/project/GetWallets.hpp"
#include "enjinsdk/project/InvalidateTokenMetadata.hpp"
#include "enjinsdk/project/MintToken.hpp"
#include "enjinsdk/project/ReleaseReserve.hpp"
#include "enjinsdk/project/SetMeltFee.hpp"
#include "enjinsdk/project/SetTransferFee.hpp"
#include "enjinsdk/project/SetTransferable.hpp"
#include "enjinsdk/project/SetUri.hpp"
#include "enjinsdk/project/SetWhitelisted.hpp"
#include "enjinsdk/project/UnlinkWallet.hpp"
#include <future>
#include <vector>

namespace enjin::sdk::project {

/// \brief Interface for project schema implementation.
class IProjectSchema {
public:
    /// \brief Default destructor.
    virtual ~IProjectSchema() = default;

    /// \brief Sends AuthPlayer request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::AccessToken>> auth_player_async(AuthPlayer& request) = 0;

    /// \brief Sends AuthPlayer request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::AccessToken> auth_player_sync(AuthPlayer& request) = 0;

    /// \brief Sends AuthProject request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::AccessToken>> auth_project_async(AuthProject& request) = 0;

    /// \brief Sends AuthProject request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::AccessToken> auth_project_sync(AuthProject& request) = 0;

    /// \brief Sends CreatePlayer request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> create_player_async(CreatePlayer& request) = 0;

    /// \brief Sends CreatePlayer request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> create_player_sync(CreatePlayer& request) = 0;

    /// \brief Sends CreateToken request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> create_token_async(CreateToken& request) = 0;

    /// \brief Sends CreateToken request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> create_token_sync(CreateToken& request) = 0;

    /// \brief Sends DecreaseMaxMeltFee request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    decrease_max_melt_fee_async(DecreaseMaxMeltFee& request) = 0;

    /// \brief Sends DecreaseMaxMeltFee request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> decrease_max_melt_fee_sync(DecreaseMaxMeltFee& request) = 0;

    /// \brief Sends DecreaseMaxTransferFee request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    decrease_max_transfer_fee_async(DecreaseMaxTransferFee& request) = 0;

    /// \brief Sends DecreaseMaxTransferFee request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request>
    decrease_max_transfer_fee_sync(DecreaseMaxTransferFee& request) = 0;

    /// \brief Sends DeletePlayer request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> delete_player_async(DeletePlayer& request) = 0;

    /// \brief Sends DeletePlayer request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<bool> delete_player_sync(DeletePlayer& request) = 0;

    /// \brief Sends GetPlayer request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Player>> get_player_async(GetPlayer& request) = 0;

    /// \brief Sends GetPlayer request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Player> get_player_sync(GetPlayer& request) = 0;

    /// \brief Sends GetPlayers request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Player>>>
    get_players_async(GetPlayers& request) = 0;

    /// \brief Sends GetPlayers request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<std::vector<models::Player>> get_players_sync(GetPlayers& request) = 0;

    /// \brief Sends GetWallet request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet_async(GetWallet& request) = 0;

    /// \brief Sends GetWallet request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Wallet> get_wallet_sync(GetWallet& request) = 0;

    /// \brief Sends GetWallets request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Wallet>>>
    get_wallets_async(GetWallets& request) = 0;

    /// \brief Sends GetWallets request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<std::vector<models::Wallet>> get_wallets_sync(GetWallets& request) = 0;

    /// \brief Sends InvalidateTokenMetadata request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>>
    invalidate_token_metadata_async(InvalidateTokenMetadata& request) = 0;

    /// \brief Sends InvalidateTokenMetadata request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<bool> invalidate_token_metadata_sync(InvalidateTokenMetadata& request) = 0;

    /// \brief Sends MintToken request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> mint_token_async(MintToken& request) = 0;

    /// \brief Sends MintToken request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> mint_token_sync(MintToken& request) = 0;

    /// \brief Sends ReleaseReserve request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> release_reserve_async(ReleaseReserve& request) = 0;

    /// \brief Sends ReleaseReserve request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> release_reserve_sync(ReleaseReserve& request) = 0;

    /// \brief Sends SetMeltFee request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_melt_fee_async(SetMeltFee& request) = 0;

    /// \brief Sends SetMeltFee request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> set_melt_fee_sync(SetMeltFee& request) = 0;

    /// \brief Sends SetTransferFee request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_transfer_fee_async(SetTransferFee& request) = 0;

    /// \brief Sends SetTransferFee request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> set_transfer_fee_sync(SetTransferFee& request) = 0;

    /// \brief Sends SetTransferable request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_transferable_async(SetTransferable& request) = 0;

    /// \brief Sends SetTransferable request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> set_transferable_sync(SetTransferable& request) = 0;

    /// \brief Sends SetUri request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_uri_async(SetUri& request) = 0;

    /// \brief Sends SetUri request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> set_uri_sync(SetUri& request) = 0;

    /// \brief Sends SetWhitelisted request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_whitelisted_async(SetWhitelisted& request) = 0;

    /// \brief Sends SetWhitelisted request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> set_whitelisted_sync(SetWhitelisted& request) = 0;

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

#endif //ENJINCPPSDK_IPROJECTSCHEMA_HPP
