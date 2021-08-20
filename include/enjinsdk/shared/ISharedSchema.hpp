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
#include "enjinsdk/shared/CancelTransaction.hpp"
#include "enjinsdk/shared/GetBalances.hpp"
#include "enjinsdk/shared/GetGasPrices.hpp"
#include "enjinsdk/shared/GetPlatform.hpp"
#include "enjinsdk/shared/GetProject.hpp"
#include "enjinsdk/shared/GetRequest.hpp"
#include "enjinsdk/shared/GetRequests.hpp"
#include "enjinsdk/shared/GetAsset.hpp"
#include "enjinsdk/shared/GetAssets.hpp"
#include <future>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Interface for shared schema implementation.
class ENJINSDK_EXPORT ISharedSchema {
public:
    /// \brief Default destructor.
    virtual ~ISharedSchema() = default;

    /// \brief Sends CancelTransaction request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> cancel_transaction_async(CancelTransaction& request) = 0;

    /// \brief Sends CancelTransaction request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<bool> cancel_transaction_sync(CancelTransaction& request) = 0;

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
};

}

#endif //ENJINCPPSDK_ISHAREDSCHEMA_HPP
