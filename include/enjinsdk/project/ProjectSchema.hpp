#ifndef ENJINCPPSDK_PROJECTSCHEMA_HPP
#define ENJINCPPSDK_PROJECTSCHEMA_HPP

#include "enjinsdk/project/IProjectSchema.hpp"
#include "enjinsdk/shared/SharedSchema.hpp"

namespace enjin::sdk::project {

/// \brief Class for sending requests in the project schema.
class ProjectSchema : public IProjectSchema,
                      public shared::SharedSchema {
public:
    ~ProjectSchema() override = default;

    std::future<graphql::GraphqlResponse<models::AccessToken>> auth_player_async(AuthPlayer& request) override;

    graphql::GraphqlResponse<models::AccessToken> auth_player_sync(AuthPlayer& request) override;

    std::future<graphql::GraphqlResponse<models::AccessToken>> auth_project_async(AuthProject& request) override;

    graphql::GraphqlResponse<models::AccessToken> auth_project_sync(AuthProject& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> create_player_async(CreatePlayer& request) override;

    graphql::GraphqlResponse<models::Request> create_player_sync(CreatePlayer& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> create_asset_async(CreateAsset& request) override;

    graphql::GraphqlResponse<models::Request> create_asset_sync(CreateAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>>
    decrease_max_melt_fee_async(DecreaseMaxMeltFee& request) override;

    graphql::GraphqlResponse<models::Request> decrease_max_melt_fee_sync(DecreaseMaxMeltFee& request) override;

    std::future<graphql::GraphqlResponse<models::Request>>
    decrease_max_transfer_fee_async(DecreaseMaxTransferFee& request) override;

    graphql::GraphqlResponse<models::Request> decrease_max_transfer_fee_sync(DecreaseMaxTransferFee& request) override;

    std::future<graphql::GraphqlResponse<bool>> delete_player_async(DeletePlayer& request) override;

    graphql::GraphqlResponse<bool> delete_player_sync(DeletePlayer& request) override;

    std::future<graphql::GraphqlResponse<models::Player>> get_player_async(GetPlayer& request) override;

    graphql::GraphqlResponse<models::Player> get_player_sync(GetPlayer& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Player>>> get_players_async(GetPlayers& request) override;

    graphql::GraphqlResponse<std::vector<models::Player>> get_players_sync(GetPlayers& request) override;

    std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet_async(GetWallet& request) override;

    graphql::GraphqlResponse<models::Wallet> get_wallet_sync(GetWallet& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Wallet>>> get_wallets_async(GetWallets& request) override;

    graphql::GraphqlResponse<std::vector<models::Wallet>> get_wallets_sync(GetWallets& request) override;

    std::future<graphql::GraphqlResponse<bool>>
    invalidate_asset_metadata_async(InvalidateAssetMetadata& request) override;

    graphql::GraphqlResponse<bool> invalidate_asset_metadata_sync(InvalidateAssetMetadata& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> mint_asset_async(MintAsset& request) override;

    graphql::GraphqlResponse<models::Request> mint_asset_sync(MintAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> release_reserve_async(ReleaseReserve& request) override;

    graphql::GraphqlResponse<models::Request> release_reserve_sync(ReleaseReserve& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_melt_fee_async(SetMeltFee& request) override;

    graphql::GraphqlResponse<models::Request> set_melt_fee_sync(SetMeltFee& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_transfer_fee_async(SetTransferFee& request) override;

    graphql::GraphqlResponse<models::Request> set_transfer_fee_sync(SetTransferFee& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_transferable_async(SetTransferable& request) override;

    graphql::GraphqlResponse<models::Request> set_transferable_sync(SetTransferable& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_uri_async(SetUri& request) override;

    graphql::GraphqlResponse<models::Request> set_uri_sync(SetUri& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> set_whitelisted_async(SetWhitelisted& request) override;

    graphql::GraphqlResponse<models::Request> set_whitelisted_sync(SetWhitelisted& request) override;

    std::future<graphql::GraphqlResponse<bool>> unlink_wallet_async(UnlinkWallet& request) override;

    graphql::GraphqlResponse<bool> unlink_wallet_sync(UnlinkWallet& request) override;

protected:
    /// \brief Constructs the schema with the middleware.
    /// \param middleware The middleware.
    explicit ProjectSchema(TrustedPlatformMiddleware middleware);
};

}

#endif //ENJINCPPSDK_PROJECTSCHEMA_HPP
