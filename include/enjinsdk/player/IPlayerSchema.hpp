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

#ifndef ENJINCPPSDK_IPLAYERSCHEMA_HPP
#define ENJINCPPSDK_IPLAYERSCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/models/Player.hpp"
#include "enjinsdk/models/Request.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include "enjinsdk/player/AdvancedSendAsset.hpp"
#include "enjinsdk/player/ApproveEnj.hpp"
#include "enjinsdk/player/ApproveMaxEnj.hpp"
#include "enjinsdk/player/BridgeAsset.hpp"
#include "enjinsdk/player/BridgeAssets.hpp"
#include "enjinsdk/player/BridgeClaimAsset.hpp"
#include "enjinsdk/player/GetPlayer.hpp"
#include "enjinsdk/player/GetWallet.hpp"
#include "enjinsdk/player/MeltAsset.hpp"
#include "enjinsdk/player/Message.hpp"
#include "enjinsdk/player/ResetEnjApproval.hpp"
#include "enjinsdk/player/SendAsset.hpp"
#include "enjinsdk/player/SendEnj.hpp"
#include "enjinsdk/player/SetApprovalForAll.hpp"
#include "enjinsdk/player/UnlinkWallet.hpp"
#include <future>
#include <vector>

namespace enjin::sdk::player {

/// \brief Interface for player schema implementation.
class ENJINSDK_EXPORT IPlayerSchema {
public:
    /// \brief Default destructor.
    virtual ~IPlayerSchema() = default;

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

    /// \brief Sends the GetPlayer request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Player>> get_player(GetPlayer request) = 0;

    /// \brief Sends the GetWallet request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Wallet>> get_wallet(GetWallet request) = 0;

    /// \brief Sends the MeltAsset request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> melt_asset(MeltAsset request) = 0;

    /// \brief Sends the Message request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> message(Message request) = 0;

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

    /// \brief Sends the UnlinkWallet request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> unlink_wallet(UnlinkWallet request) = 0;
};

}

#endif //ENJINCPPSDK_IPLAYERSCHEMA_HPP
