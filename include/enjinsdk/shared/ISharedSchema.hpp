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
#include "enjinsdk/shared/GetTransaction.hpp"
#include "enjinsdk/shared/GetTransactions.hpp"
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

    /// \brief Sends the CancelTransaction request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> cancel_transaction(CancelTransaction request) = 0;

    /// \brief Sends the GetBalances request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Balance>>> get_balances(GetBalances request) = 0;

    /// \brief Sends the GetGasPrices request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::GasPrices>> get_gas_prices(GetGasPrices request) = 0;

    /// \brief Sends the GetPlatform request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Platform>> get_platform(GetPlatform request) = 0;

    /// \brief Sends the GetProject request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Project>> get_project(GetProject request) = 0;

    /// \brief Sends the GetRequest request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> get_request(GetTransaction request) = 0;

    /// \brief Sends the GetRequests request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Request>>> get_requests(GetTransactions request) = 0;

    /// \brief Sends the GetAsset request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Asset>> get_asset(GetAsset request) = 0;

    /// \brief Sends the GetAssets request to the platform.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Asset>>> get_assets(GetAssets request) = 0;
};

}

#endif //ENJINCPPSDK_ISHAREDSCHEMA_HPP
