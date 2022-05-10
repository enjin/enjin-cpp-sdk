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

#ifndef ENJINSDK_TESTABLEBASESCHEMA_HPP
#define ENJINSDK_TESTABLEBASESCHEMA_HPP

#include "enjinsdk/BaseSchema.hpp"
#include "enjinsdk/IHttpClient.hpp"
#include <string>

namespace enjin::test::utils {

class TestableBaseSchema : public sdk::BaseSchema {
public:
    TestableBaseSchema() = delete;

    explicit TestableBaseSchema(std::unique_ptr<sdk::http::IHttpClient> http_client);

    ~TestableBaseSchema() = default;

    const std::unique_ptr<sdk::ClientMiddleware>& get_middleware();

    std::string create_request_body(sdk::graphql::AbstractGraphqlRequest& request);

    sdk::http::HttpRequest create_request(sdk::graphql::AbstractGraphqlRequest& request);

    template<class T>
    std::future<sdk::graphql::GraphqlResponse<T>> send_request_for_one(sdk::graphql::AbstractGraphqlRequest& request) {
        return BaseSchema::send_request_for_one<T>(request);
    }

    template<class T>
    std::future<sdk::graphql::GraphqlResponse<std::vector<T>>>
    send_request_for_many(sdk::graphql::AbstractGraphqlRequest& request) {
        return BaseSchema::send_request_for_many<T>(request);
    }
};

}

#endif //ENJINSDK_TESTABLEBASESCHEMA_HPP
