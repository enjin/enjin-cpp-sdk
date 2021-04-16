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

#ifndef ENJINCPPSDK_SHAREDSCHEMA_HPP
#define ENJINCPPSDK_SHAREDSCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/BaseSchema.hpp"
#include "enjinsdk/shared/ISharedSchema.hpp"
#include <string>

namespace enjin::sdk::shared {

/// \brief Class for sending requests shared across schemas.
class ENJINSDK_EXPORT SharedSchema : public ISharedSchema,
                                     public BaseSchema {
public:
    SharedSchema() = delete;

    ~SharedSchema() override = default;

    std::future<graphql::GraphqlResponse<models::Request>>
    advanced_send_asset_async(AdvancedSendAsset& request) override;

    graphql::GraphqlResponse<models::Request> advanced_send_asset_sync(AdvancedSendAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj_async(ApproveEnj& request) override;

    graphql::GraphqlResponse<models::Request> approve_enj_sync(ApproveEnj& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj_max_async(ApproveMaxEnj& request) override;

    graphql::GraphqlResponse<models::Request> approve_enj_max_sync(ApproveMaxEnj& request) override;

    std::future<graphql::GraphqlResponse<bool>> cancel_transaction_async(CancelTransaction& request) override;

    graphql::GraphqlResponse<bool> cancel_transaction_sync(CancelTransaction& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> complete_trade_async(CompleteTrade& request) override;

    graphql::GraphqlResponse<models::Request> complete_trade_sync(CompleteTrade& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> create_trade_async(CreateTrade& request) override;

    graphql::GraphqlResponse<models::Request> create_trade_sync(CreateTrade& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Balance>>>
    get_balances_async(GetBalances& request) override;

    graphql::GraphqlResponse<std::vector<models::Balance>> get_balances_sync(GetBalances& request) override;

    std::future<graphql::GraphqlResponse<models::GasPrices>> get_gas_prices_async(GetGasPrices& request) override;

    graphql::GraphqlResponse<models::GasPrices> get_gas_prices_sync(GetGasPrices& request) override;

    std::future<graphql::GraphqlResponse<models::Platform>> get_platform_async(GetPlatform& request) override;

    graphql::GraphqlResponse<models::Platform> get_platform_sync(GetPlatform& request) override;

    std::future<graphql::GraphqlResponse<models::Project>> get_project_async(GetProject& request) override;

    graphql::GraphqlResponse<models::Project> get_project_sync(GetProject& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> get_request_async(GetRequest& request) override;

    graphql::GraphqlResponse<models::Request> get_request_sync(GetRequest& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Request>>>
    get_requests_async(GetRequests& request) override;

    graphql::GraphqlResponse<std::vector<models::Request>> get_requests_sync(GetRequests& request) override;

    std::future<graphql::GraphqlResponse<models::Asset>> get_asset_async(GetAsset& request) override;

    graphql::GraphqlResponse<models::Asset> get_asset_sync(GetAsset& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Asset>>> get_assets_async(GetAssets& request) override;

    graphql::GraphqlResponse<std::vector<models::Asset>> get_assets_sync(GetAssets& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> melt_asset_async(MeltAsset& request) override;

    graphql::GraphqlResponse<models::Request> melt_asset_sync(MeltAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> message_async(Message& request) override;

    graphql::GraphqlResponse<models::Request> message_sync(Message& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> reset_enj_approval_async(ResetEnjApproval& request) override;

    graphql::GraphqlResponse<models::Request> reset_enj_approval_sync(ResetEnjApproval& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_enj_async(SendEnj& request) override;

    graphql::GraphqlResponse<models::Request> send_enj_sync(SendEnj& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_asset_async(SendAsset& request) override;

    graphql::GraphqlResponse<models::Request> send_asset_sync(SendAsset& request) override;

    std::future<graphql::GraphqlResponse<models::Request>>
    set_approval_for_all_async(SetApprovalForAll& request) override;

    graphql::GraphqlResponse<models::Request> set_approval_for_all_sync(SetApprovalForAll& request) override;

protected:
    /// \brief Constructs the schema with the middleware and name.
    /// \param middleware The middleware.
    /// \param schema The schema name.
    /// \param logger The logger.
    SharedSchema(TrustedPlatformMiddleware middleware,
                 const std::string& schema,
                 std::shared_ptr<utils::Logger> logger);
};

}

#endif //ENJINCPPSDK_SHAREDSCHEMA_HPP
