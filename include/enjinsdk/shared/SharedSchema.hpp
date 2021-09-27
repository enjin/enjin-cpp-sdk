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

    std::future<graphql::GraphqlResponse<bool>> cancel_transaction(CancelTransaction& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Balance>>> get_balances(GetBalances& request) override;

    std::future<graphql::GraphqlResponse<models::GasPrices>> get_gas_prices(GetGasPrices& request) override;

    std::future<graphql::GraphqlResponse<models::Platform>> get_platform(GetPlatform& request) override;

    std::future<graphql::GraphqlResponse<models::Project>> get_project(GetProject& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> get_request(GetRequest& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Request>>> get_requests(GetRequests& request) override;

    std::future<graphql::GraphqlResponse<models::Asset>> get_asset(GetAsset& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Asset>>> get_assets(GetAssets& request) override;

protected:
    /// \brief Constructs the schema with the middleware and name.
    /// \param middleware The middleware.
    /// \param schema The schema name.
    /// \param logger_provider The logger provider.
    SharedSchema(TrustedPlatformMiddleware middleware,
                 const std::string& schema,
                 std::shared_ptr<utils::LoggerProvider> logger_provider);
};

}

#endif //ENJINCPPSDK_SHAREDSCHEMA_HPP
