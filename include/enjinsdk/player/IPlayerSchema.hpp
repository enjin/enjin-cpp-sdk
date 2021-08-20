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
