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

#include <enjinsdk/shared/SharedSchema.hpp>

#include <utility>

namespace enjin::sdk::shared {

SharedSchema::SharedSchema(std::unique_ptr<http::IHttpClient> http_client,
                           std::string schema,
                           std::shared_ptr<utils::LoggerProvider> logger_provider)
        : BaseSchema(std::move(http_client), std::move(schema), std::move(logger_provider)) {
}

std::future<graphql::GraphqlResponse<bool>> SharedSchema::cancel_transaction(CancelTransaction request) {
    return send_request_for_one<bool>(request);
}

std::future<graphql::GraphqlResponse<std::vector<models::Balance>>> SharedSchema::get_balances(GetBalances request) {
    return send_request_for_many<models::Balance>(request);
}

std::future<graphql::GraphqlResponse<models::GasPrices>> SharedSchema::get_gas_prices(GetGasPrices request) {
    return send_request_for_one<models::GasPrices>(request);
}

std::future<graphql::GraphqlResponse<models::Platform>> SharedSchema::get_platform(GetPlatform request) {
    return send_request_for_one<models::Platform>(request);
}

std::future<graphql::GraphqlResponse<models::Project>> SharedSchema::get_project(GetProject request) {
    return send_request_for_one<models::Project>(request);
}

std::future<graphql::GraphqlResponse<models::Transaction>> SharedSchema::get_request(GetTransaction request) {
    return send_request_for_one<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<std::vector<models::Transaction>>> SharedSchema::get_requests(GetTransactions request) {
    return send_request_for_many<models::Transaction>(request);
}

std::future<graphql::GraphqlResponse<models::Asset>> SharedSchema::get_asset(GetAsset request) {
    return send_request_for_one<models::Asset>(request);
}

std::future<graphql::GraphqlResponse<std::vector<models::Asset>>> SharedSchema::get_assets(GetAssets request) {
    return send_request_for_many<models::Asset>(request);
}

}
