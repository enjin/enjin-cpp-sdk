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

#include "enjinsdk/BaseSchema.hpp"

#include "RapidJsonUtils.hpp"
#include <sstream>
#include <string>

namespace enjin::sdk {

BaseSchema::BaseSchema(TrustedPlatformMiddleware middleware,
                       std::string schema,
                       std::shared_ptr<utils::LoggerProvider> logger_provider)
        : middleware(std::move(middleware)),
          logger_provider(std::move(logger_provider)),
          schema(std::move(schema)) {
}

std::string BaseSchema::create_request_body(graphql::AbstractGraphqlRequest& request) const {
    rapidjson::Document document(rapidjson::kObjectType);

    utils::set_string_member(document,
                             "query",
                             middleware.get_query_registry().get_operation_for_name(request.get_namespace()));
    utils::set_object_member_from_string(document, "variables", request.serialize());

    return utils::document_to_string(document);
}

http::HttpRequest BaseSchema::create_request(graphql::AbstractGraphqlRequest& request) const {
    auto req = http::HttpRequest().set_method(http::HttpMethod::POST)
                                  .set_path_query_fragment(std::string("/graphql/").append(schema))
                                  .set_content_type(JSON)
                                  .set_body(create_request_body(request));

    // Adds the default SDK user agent header using the defined SDK version if the definition was set
    std::stringstream user_agent_ss;
    user_agent_ss << http::TrustedPlatformHandler::USER_AGENT_PREFIX;

#ifdef ENJINSDK_VERSION
    user_agent_ss << ENJINSDK_VERSION;
#else
    user_agent_ss << "?";
#endif

    req.add_header(http::TrustedPlatformHandler::USER_AGENT, user_agent_ss.str());

    // Adds authorization header if SDK has been authenticated
    auto& tp_handler = middleware.get_handler();
    if (tp_handler != nullptr && tp_handler->is_authenticated()) {
        std::stringstream authorization_ss;
        authorization_ss << http::TrustedPlatformHandler::AUTHORIZATION_SCHEMA
                         << " "
                         << tp_handler->get_auth_token().value();

        req.add_header(http::TrustedPlatformHandler::AUTHORIZATION, authorization_ss.str());
    }

    return req;
}

const std::shared_ptr<utils::LoggerProvider>& BaseSchema::get_logger_provider() const {
    return logger_provider;
}

void BaseSchema::log_graphql_exception(const std::exception& e) {
    if (logger_provider == nullptr) {
        return;
    }

    std::stringstream ss;
    ss << "An exception occurred processing GraphQL response: " << e.what();
    logger_provider->log(utils::LogLevel::SEVERE, ss.str());
}

http::HttpResponse BaseSchema::send_request(http::HttpRequest request) {
    return middleware.get_client()->send_request(request).get();
}

}
