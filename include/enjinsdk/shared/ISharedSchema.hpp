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

#ifndef ENJINCPPSDK_ISHAREDSCHEMA_HPP
#define ENJINCPPSDK_ISHAREDSCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/models/Balance.hpp"
#include "enjinsdk/models/GasPrices.hpp"
#include "enjinsdk/models/Platform.hpp"
#include "enjinsdk/models/Project.hpp"
#include "enjinsdk/models/Request.hpp"
#include "enjinsdk/models/Asset.hpp"
#include "enjinsdk/shared/AdvancedSendAsset.hpp"
#include "enjinsdk/shared/ApproveEnj.hpp"
#include "enjinsdk/shared/ApproveMaxEnj.hpp"
#include "enjinsdk/shared/CancelTransaction.hpp"
#include "enjinsdk/shared/CompleteTrade.hpp"
#include "enjinsdk/shared/CreateTrade.hpp"
#include "enjinsdk/shared/GetBalances.hpp"
#include "enjinsdk/shared/GetGasPrices.hpp"
#include "enjinsdk/shared/GetPlatform.hpp"
#include "enjinsdk/shared/GetProject.hpp"
#include "enjinsdk/shared/GetRequest.hpp"
#include "enjinsdk/shared/GetRequests.hpp"
#include "enjinsdk/shared/GetAsset.hpp"
#include "enjinsdk/shared/GetAssets.hpp"
#include "enjinsdk/shared/MeltAsset.hpp"
#include "enjinsdk/shared/Message.hpp"
#include "enjinsdk/shared/ResetEnjApproval.hpp"
#include "enjinsdk/shared/SendEnj.hpp"
#include "enjinsdk/shared/SendAsset.hpp"
#include "enjinsdk/shared/SetApprovalForAll.hpp"
#include <future>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Interface for shared schema implementation.
class ENJINSDK_EXPORT ISharedSchema {
public:
    /// \brief Default destructor.
    virtual ~ISharedSchema() = default;

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

    /// \brief Sends CancelTransaction request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> cancel_transaction_async(CancelTransaction& request) = 0;

    /// \brief Sends CancelTransaction request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<bool> cancel_transaction_sync(CancelTransaction& request) = 0;

    /// \brief Sends CompleteTrade request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> complete_trade_async(CompleteTrade& request) = 0;

    /// \brief Sends CompleteTrade request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> complete_trade_sync(CompleteTrade& request) = 0;

    /// \brief Sends CreateTrade request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> create_trade_async(CreateTrade& request) = 0;

    /// \brief Sends CreateTrade request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> create_trade_sync(CreateTrade& request) = 0;

    /// \brief Sends GetBalances request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Balance>>>
    get_balances_async(GetBalances& request) = 0;

    /// \brief Sends GetBalances request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<std::vector<models::Balance>> get_balances_sync(GetBalances& request) = 0;

    /// \brief Sends GetGasPrices request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::GasPrices>> get_gas_prices_async(GetGasPrices& request) = 0;

    /// \brief Sends GetGasPrices request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::GasPrices> get_gas_prices_sync(GetGasPrices& request) = 0;

    /// \brief Sends GetPlatform request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Platform>> get_platform_async(GetPlatform& request) = 0;

    /// \brief Sends GetPlatform request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Platform> get_platform_sync(GetPlatform& request) = 0;

    /// \brief Sends GetProject request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Project>> get_project_async(GetProject& request) = 0;

    /// \brief Sends GetProject request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Project> get_project_sync(GetProject& request) = 0;

    /// \brief Sends GetRequest request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> get_request_async(GetRequest& request) = 0;

    /// \brief Sends GetRequest request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> get_request_sync(GetRequest& request) = 0;

    /// \brief Sends GetRequests request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Request>>>
    get_requests_async(GetRequests& request) = 0;

    /// \brief Sends GetRequests request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<std::vector<models::Request>> get_requests_sync(GetRequests& request) = 0;

    /// \brief Sends GetAsset request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Asset>> get_asset_async(GetAsset& request) = 0;

    /// \brief Sends GetAsset request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Asset> get_asset_sync(GetAsset& request) = 0;

    /// \brief Sends GetAssets request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Asset>>> get_assets_async(GetAssets& request) = 0;

    /// \brief Sends GetAssets request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<std::vector<models::Asset>> get_assets_sync(GetAssets& request) = 0;

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

    /// \brief Sends SendEnj request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> send_enj_async(SendEnj& request) = 0;

    /// \brief Sends SendEnj request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> send_enj_sync(SendEnj& request) = 0;

    /// \brief Sends SendAsset request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> send_asset_async(SendAsset& request) = 0;

    /// \brief Sends SendAsset request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> send_asset_sync(SendAsset& request) = 0;

    /// \brief Sends SetApprovalForAll request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    set_approval_for_all_async(SetApprovalForAll& request) = 0;

    /// \brief Sends SetApprovalForAll request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> set_approval_for_all_sync(SetApprovalForAll& request) = 0;
};

}

#endif //ENJINCPPSDK_ISHAREDSCHEMA_HPP
