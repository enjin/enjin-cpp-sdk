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

#include <enjinsdk/shared/SharedSchema.hpp>

#include <utility>

namespace enjin::sdk::shared {

SharedSchema::SharedSchema(TrustedPlatformMiddleware middleware,
                           const std::string& schema,
                           std::shared_ptr<utils::LoggerProvider> logger_provider)
        : BaseSchema(std::move(middleware), schema, std::move(logger_provider)) {
}

std::future<graphql::GraphqlResponse<bool>> SharedSchema::cancel_transaction_async(CancelTransaction& request) {
    return send_request_for_one<bool>(request);
}

graphql::GraphqlResponse<bool> SharedSchema::cancel_transaction_sync(CancelTransaction& request) {
    return send_request_for_one<bool>(request).get();
}

std::future<graphql::GraphqlResponse<std::vector<models::Balance>>>
SharedSchema::get_balances_async(GetBalances& request) {
    return send_request_for_many<models::Balance>(request);
}

graphql::GraphqlResponse<std::vector<models::Balance>> SharedSchema::get_balances_sync(GetBalances& request) {
    return send_request_for_many<models::Balance>(request).get();
}

std::future<graphql::GraphqlResponse<models::GasPrices>> SharedSchema::get_gas_prices_async(GetGasPrices& request) {
    return send_request_for_one<models::GasPrices>(request);
}

graphql::GraphqlResponse<models::GasPrices> SharedSchema::get_gas_prices_sync(GetGasPrices& request) {
    return send_request_for_one<models::GasPrices>(request).get();
}

std::future<graphql::GraphqlResponse<models::Platform>> SharedSchema::get_platform_async(GetPlatform& request) {
    return send_request_for_one<models::Platform>(request);
}

graphql::GraphqlResponse<models::Platform> SharedSchema::get_platform_sync(GetPlatform& request) {
    return send_request_for_one<models::Platform>(request).get();
}

std::future<graphql::GraphqlResponse<models::Project>> SharedSchema::get_project_async(GetProject& request) {
    return send_request_for_one<models::Project>(request);
}

graphql::GraphqlResponse<models::Project> SharedSchema::get_project_sync(GetProject& request) {
    return send_request_for_one<models::Project>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::get_request_async(GetRequest& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::get_request_sync(GetRequest& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<std::vector<models::Request>>>
SharedSchema::get_requests_async(GetRequests& request) {
    return send_request_for_many<models::Request>(request);
}

graphql::GraphqlResponse<std::vector<models::Request>> SharedSchema::get_requests_sync(GetRequests& request) {
    return send_request_for_many<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Asset>> SharedSchema::get_asset_async(GetAsset& request) {
    return send_request_for_one<models::Asset>(request);
}

graphql::GraphqlResponse<models::Asset> SharedSchema::get_asset_sync(GetAsset& request) {
    return send_request_for_one<models::Asset>(request).get();
}

std::future<graphql::GraphqlResponse<std::vector<models::Asset>>> SharedSchema::get_assets_async(GetAssets& request) {
    return send_request_for_many<models::Asset>(request);
}

graphql::GraphqlResponse<std::vector<models::Asset>> SharedSchema::get_assets_sync(GetAssets& request) {
    return send_request_for_many<models::Asset>(request).get();
}

}
