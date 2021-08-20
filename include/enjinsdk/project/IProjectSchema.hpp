/* Copyright 2021 Enjin Pte Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ENJINCPPSDK_IPROJECTSCHEMA_HPP
#define ENJINCPPSDK_IPROJECTSCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/models/AccessToken.hpp"
#include "enjinsdk/models/Player.hpp"
#include "enjinsdk/models/Request.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include "enjinsdk/project/AdvancedSendAsset.hpp"
#include "enjinsdk/project/ApproveEnj.hpp"
#include "enjinsdk/project/ApproveMaxEnj.hpp"
#include "enjinsdk/project/AuthPlayer.hpp"
#include "enjinsdk/project/AuthProject.hpp"
#include "enjinsdk/project/CompleteTrade.hpp"
#include "enjinsdk/project/CreateAsset.hpp"
#include "enjinsdk/project/CreatePlayer.hpp"
#include "enjinsdk/project/CreateTrade.hpp"
#include "enjinsdk/project/DecreaseMaxMeltFee.hpp"
#include "enjinsdk/project/DecreaseMaxTransferFee.hpp"
#include "enjinsdk/project/DeletePlayer.hpp"
#include "enjinsdk/project/GetPlayer.hpp"
#include "enjinsdk/project/GetPlayers.hpp"
#include "enjinsdk/project/GetWallet.hpp"
#include "enjinsdk/project/GetWallets.hpp"
#include "enjinsdk/project/InvalidateAssetMetadata.hpp"
#include "enjinsdk/project/MeltAsset.hpp"
#include "enjinsdk/project/Message.hpp"
#include "enjinsdk/project/MintAsset.hpp"
#include "enjinsdk/project/ReleaseReserve.hpp"
#include "enjinsdk/project/ResetEnjApproval.hpp"
#include "enjinsdk/project/SendEnj.hpp"
#include "enjinsdk/project/SendAsset.hpp"
#include "enjinsdk/project/SetApprovalForAll.hpp"
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
class ENJINSDK_EXPORT IProjectSchema {
public:
    /// \brief Default destructor.
    virtual ~IProjectSchema() = default;

    /// \brief Sends AdvancedSendAsset request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    advanced_send_asset_async(AdvancedSendAsset& request) = 0;

    /// \brief Sends AdvancedSendAsset request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> advanced_send_asset_sync(AdvancedSendAsset& request) = 0;

    /// \brief Sends ApproveEnj request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> approve_enj_async(ApproveEnj& request) = 0;

    /// \brief Sends ApproveEnj request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> approve_enj_sync(ApproveEnj& request) = 0;

    /// \brief Sends ApproveMaxEnj request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> approve_enj_max_async(ApproveMaxEnj& request) = 0;

    /// \brief Sends ApproveMaxEnj request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> approve_enj_max_sync(ApproveMaxEnj& request) = 0;

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

    /// \brief Sends CompleteTrade request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> complete_trade_async(CompleteTrade& request) = 0;

    /// \brief Sends CompleteTrade request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> complete_trade_sync(CompleteTrade& request) = 0;

    /// \brief Sends CreateAsset request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> create_asset_async(CreateAsset& request) = 0;

    /// \brief Sends CreateAsset request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> create_asset_sync(CreateAsset& request) = 0;

    /// \brief Sends CreatePlayer request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> create_player_async(CreatePlayer& request) = 0;

    /// \brief Sends CreatePlayer request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> create_player_sync(CreatePlayer& request) = 0;

    /// \brief Sends CreateTrade request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> create_trade_async(CreateTrade& request) = 0;

    /// \brief Sends CreateTrade request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> create_trade_sync(CreateTrade& request) = 0;

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

    /// \brief Sends InvalidateAssetMetadata request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>>
    invalidate_asset_metadata_async(InvalidateAssetMetadata& request) = 0;

    /// \brief Sends InvalidateAssetMetadata request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<bool> invalidate_asset_metadata_sync(InvalidateAssetMetadata& request) = 0;

    /// \brief Sends MeltAsset request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> melt_asset_async(MeltAsset& request) = 0;

    /// \brief Sends MeltAsset request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> melt_asset_sync(MeltAsset& request) = 0;

    /// \brief Sends Message request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> message_async(Message& request) = 0;

    /// \brief Sends Message request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> message_sync(Message& request) = 0;

    /// \brief Sends MintAsset request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> mint_asset_async(MintAsset& request) = 0;

    /// \brief Sends MintAsset request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> mint_asset_sync(MintAsset& request) = 0;

    /// \brief Sends ReleaseReserve request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> release_reserve_async(ReleaseReserve& request) = 0;

    /// \brief Sends ReleaseReserve request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> release_reserve_sync(ReleaseReserve& request) = 0;

    /// \brief Sends ResetEnjApproval request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    reset_enj_approval_async(ResetEnjApproval& request) = 0;

    /// \brief Sends ResetEnjApproval request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> reset_enj_approval_sync(ResetEnjApproval& request) = 0;

    /// \brief Sends SendAsset request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> send_asset_async(SendAsset& request) = 0;

    /// \brief Sends SendAsset request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> send_asset_sync(SendAsset& request) = 0;

    /// \brief Sends SendEnj request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> send_enj_async(SendEnj& request) = 0;

    /// \brief Sends SendEnj request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> send_enj_sync(SendEnj& request) = 0;

    /// \brief Sends SetApprovalForAll request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    set_approval_for_all_async(SetApprovalForAll& request) = 0;

    /// \brief Sends SetApprovalForAll request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> set_approval_for_all_sync(SetApprovalForAll& request) = 0;

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
