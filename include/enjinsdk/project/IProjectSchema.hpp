/* Copyright 2021 Enjin Pte. Ltd.
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
#include "enjinsdk/project/BridgeAsset.hpp"
#include "enjinsdk/project/BridgeAssets.hpp"
#include "enjinsdk/project/BridgeClaimAsset.hpp"
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

    /// \brief Sends the AdvancedSendAsset request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> advanced_send_asset(AdvancedSendAsset request) = 0;

    /// \brief Sends the ApproveEnj request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> approve_enj(ApproveEnj request) = 0;

    /// \brief Sends the ApproveMaxEnj request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> approve_enj_max(ApproveMaxEnj request) = 0;

    /// \brief Sends the AuthPlayer request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::AccessToken>> auth_player(AuthPlayer request) = 0;

    /// \brief Sends the AuthProject request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::AccessToken>> auth_project(AuthProject request) = 0;

    /// \brief Sends the BridgeAsset request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> bridge_asset(BridgeAsset request) = 0;

    /// \brief Sends the BridgeAssets request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> bridge_assets(BridgeAssets request) = 0;

    /// \brief Sends the BridgeClaimAsset request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> bridge_claim_asset(BridgeClaimAsset request) = 0;

    /// \brief Sends the CompleteTrade request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> complete_trade(CompleteTrade request) = 0;

    /// \brief Sends the CreateAsset request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> create_asset(CreateAsset request) = 0;

    /// \brief Sends the CreatePlayer request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::AccessToken>> create_player(CreatePlayer request) = 0;

    /// \brief Sends the CreateTrade request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> create_trade(CreateTrade request) = 0;

    /// \brief Sends the DecreaseMaxMeltFee request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    decrease_max_melt_fee(DecreaseMaxMeltFee request) = 0;

    /// \brief Sends the DecreaseMaxTransferFee request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    decrease_max_transfer_fee(DecreaseMaxTransferFee request) = 0;

    /// \brief Sends the DeletePlayer request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> delete_player(DeletePlayer request) = 0;

    /// \brief Sends the GetPlayer request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Player>> get_player(GetPlayer request) = 0;

    /// \brief Sends the GetPlayers request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Player>>> get_players(GetPlayers request) = 0;

    /// \brief Sends the GetWallet request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet(GetWallet request) = 0;

    /// \brief Sends the GetWallets request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Wallet>>> get_wallets(GetWallets request) = 0;

    /// \brief Sends the InvalidateAssetMetadata request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> invalidate_asset_metadata(InvalidateAssetMetadata request) = 0;

    /// \brief Sends the MeltAsset request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> melt_asset(MeltAsset request) = 0;

    /// \brief Sends the Message request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> message(Message request) = 0;

    /// \brief Sends the MintAsset request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> mint_asset(MintAsset request) = 0;

    /// \brief Sends the ReleaseReserve request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> release_reserve(ReleaseReserve request) = 0;

    /// \brief Sends the ResetEnjApproval request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> reset_enj_approval(ResetEnjApproval request) = 0;

    /// \brief Sends the SendAsset request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> send_asset(SendAsset request) = 0;

    /// \brief Sends the SendEnj request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> send_enj(SendEnj request) = 0;

    /// \brief Sends the SetApprovalForAll request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_approval_for_all(SetApprovalForAll request) = 0;

    /// \brief Sends the SetMeltFee request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_melt_fee(SetMeltFee request) = 0;

    /// \brief Sends the SetTransferFee request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_transfer_fee(SetTransferFee request) = 0;

    /// \brief Sends the SetTransferable request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_transferable(SetTransferable request) = 0;

    /// \brief Sends the SetUri request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_uri(SetUri request) = 0;

    /// \brief Sends the SetWhitelisted request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> set_whitelisted(SetWhitelisted request) = 0;

    /// \brief Sends the UnlinkWallet request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> unlink_wallet(UnlinkWallet request) = 0;
};

}

#endif //ENJINCPPSDK_IPROJECTSCHEMA_HPP
