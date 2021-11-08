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

#include "enjinsdk/TrustedPlatformMiddleware.hpp"

#include <stdexcept>
#include <utility>

namespace enjin::sdk {

TrustedPlatformMiddleware::TrustedPlatformMiddleware(std::unique_ptr<http::IHttpClient> client)
        : client(std::move(client)) {
    if (TrustedPlatformMiddleware::client == nullptr) {
        throw std::runtime_error("Nullptr for HTTP client on TrustedPlatformMiddleware construction.");
    }

    TrustedPlatformMiddleware::client->start();
}

void TrustedPlatformMiddleware::close() {
    if (client == nullptr) {
        return;
    }

    client->stop();
}

const graphql::GraphqlQueryRegistry& TrustedPlatformMiddleware::get_query_registry() const {
    return query_registry;
}

const std::unique_ptr<http::IHttpClient>& TrustedPlatformMiddleware::get_client() const {
    return client;
}

const std::shared_ptr<http::TrustedPlatformHandler>& TrustedPlatformMiddleware::get_handler() const {
    return handler;
}

bool TrustedPlatformMiddleware::is_closed() const {
    return client == nullptr || !client->is_open();
}

}
