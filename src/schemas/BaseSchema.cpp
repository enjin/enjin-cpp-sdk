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

using namespace enjin::sdk;
using namespace enjin::sdk::graphql;
using namespace enjin::sdk::http;
using namespace enjin::sdk::utils;

BaseSchema::BaseSchema(std::unique_ptr<IHttpClient> http_client,
                       std::string schema,
                       std::shared_ptr<LoggerProvider> logger_provider)
        : middleware(std::make_unique<TrustedPlatformMiddleware>(std::move(http_client))),
          logger_provider(std::move(logger_provider)),
          schema(std::move(schema)) {
}

std::string BaseSchema::create_request_body(AbstractGraphqlRequest& request) const {
    rapidjson::Document document(rapidjson::kObjectType);

    utils::set_string_member(document,
                             "query",
                             middleware->get_query_registry().get_operation_for_name(request.get_namespace()));
    utils::set_object_member_from_string(document, "variables", request.serialize());

    return utils::document_to_string(document);
}

HttpRequest BaseSchema::create_request(AbstractGraphqlRequest& request) const {
    HttpRequest req = middleware->create_request();

    req.set_method(HttpMethod::POST)
       .set_path_query_fragment(std::string("/graphql/").append(schema))
       .set_content_type(JSON)
       .set_body(create_request_body(request));

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
    return middleware->get_client()->send_request(request).get();
}
