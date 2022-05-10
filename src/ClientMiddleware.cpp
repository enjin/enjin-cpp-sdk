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

#include "enjinsdk/ClientMiddleware.hpp"

#include "enjinsdk/HttpHeaders.hpp"
#include "enjinsdk_utils/StringUtils.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::utils;

ClientMiddleware::ClientMiddleware(std::unique_ptr<IHttpClient> client) : client(std::move(client)) {
    if (this->client == nullptr) {
        throw std::runtime_error("Nullptr for HTTP client on TrustedPlatformMiddleware construction.");
    }

    // Adds the default SDK user agent header using the defined SDK version if the definition was set
    std::stringstream user_agent_ss;
    user_agent_ss << USER_AGENT_PREFIX;

#ifdef ENJINSDK_VERSION
    user_agent_ss << ENJINSDK_VERSION;
#else
    user_agent_ss << "?";
#endif

    this->client->set_default_request_header(USER_AGENT, user_agent_ss.str());
    this->client->start();
}

void ClientMiddleware::close() {
    if (client == nullptr) {
        return;
    }

    client->stop();
}

HttpRequest ClientMiddleware::create_request() const {
    HttpRequest req;

    {
        std::lock_guard<std::mutex> guard(auth_token_mutex);
        if (!auth_token.empty()) {
            std::stringstream ss;
            ss << AUTHORIZATION_SCHEMA << " " << auth_token;

            req.add_header(AUTHORIZATION, ss.str());
        }
    }

    return req;
}

const graphql::GraphqlQueryRegistry& ClientMiddleware::get_query_registry() const {
    return query_registry;
}

const std::unique_ptr<http::IHttpClient>& ClientMiddleware::get_client() const {
    return client;
}

bool ClientMiddleware::is_closed() const {
    return client == nullptr || !client->is_open();
}

void ClientMiddleware::set_auth_token(std::string token) {
    std::lock_guard<std::mutex> guard(auth_token_mutex);
    auth_token = std::move(token);
}

bool ClientMiddleware::is_authenticated() const {
    std::lock_guard<std::mutex> guard(auth_token_mutex);
    return !is_empty_or_whitespace(auth_token);
}
